/* Sprite.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

TODO header's header (sprite description lmao)
TODO Crop() (which crops the sprite itself) and Subcrop() (which returns the cropped sprite of the current sprite)

SPRITE BINARY FILE FORMAT
--First byte - width in range 0-255 (0x00-0xFF)

--Second byte - height in range 0-255 (0x00-0xFF)

Each sprite pixel is usually 3 bytes:
--First byte - two colors combined such as: byte = firstColor*16+secondColor
	Can be easily retrieved as firstColor(byte/16), secondColor(byte%16)

--Second and third bytes represent UTF16 with big endian encoding 2-byte symbol (wchar_t), such as:
	symbolVal = thirdByte * 256 + fourthByte;

NOTE: Pixel considered empty or transparent when either of two colors is equal to 0xFF (cTransparent)
	Empty pixels take up only one byte and stored as 0x10 value (thus 2 bytes for symbol are just ignored)

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/

//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Creates sprite file for debug purposes
	void __Sprite::debug_create()
	{
		/* F U C C
		int w = 3, h = 3;
		data.foregroundColor.resize(h, std::vector<__ConsoleColor>(w, cGreen));
		data.backgroundColor.resize(h, std::vector<__ConsoleColor>(w, cBlack));
		data.character.resize(h, std::vector<wchar_t>(w, 0xFF));

		//non transparent
		data.backgroundColor[1][1] = cCyan;
		data.foregroundColor[1][1] = cWhite;
		data.character[1][1] = 0x256C;

		std::vector<unsigned int> bytes;
		bytes.push_back(data.foregroundColor.size());
		bytes.push_back(data.foregroundColor[0].size());

		for (int i = 0; i < data.foregroundColor.size(); i++)
		{
			for (int j = 0; j < data.foregroundColor[i].size(); j++)
			{
				if (data.foregroundColor[i][j] == cTransparent || data.backgroundColor[i][j] == cTransparent)
					bytes.push_back(255);

				if (data.backgroundColor[i][j] == cTransparent)
					bytes.push_back(255);
				else
					bytes.push_back(data.backgroundColor[i][j]);

				bytes.push_back(data.character[i][j]);
			}
		}
		std::ofstream outputFile("EngineCoreRaw/Sprites/test.ytf", std::ios::binary);
		for (int i = 0, offset = 0; i < bytes.size(); i++)
		{
			if (((i - 2) % 3) == 0 && i > 1 && bytes[i] == 0xff && bytes[i + 1] == 0xff)
			{
				outputFile.seekp(i + offset);
				outputFile << (unsigned char)(0x10);

				i += 2;
				offset -= 2;
				continue;
			}

			if (((i - 4) % 3) == 0 && i > 1)
			{
				outputFile.seekp(i + offset);
				outputFile << (unsigned char)(bytes[i] / 256) << (unsigned char)(bytes[i] % 256);
				offset++;
			}
			else
			{
				outputFile.seekp(i + offset);
				outputFile << (unsigned char)bytes[i];
			}
		}*/
	}




	//Constructor without sprite load
	__Sprite::__Sprite(const std::shared_ptr<__Project> & pr) : project(pr)
	{
		Init();
	}

	//Constructor with sprite load
	__Sprite::__Sprite(const std::shared_ptr<__Project> & pr, const __Location & loc) : project(pr)
	{
		//Init() is called in Load()
		Load(loc);
	}

	__Sprite::~__Sprite() {	}

	//Initializes all variables
	void __Sprite::Init()
	{
		name = std::wstring();
		data = __SpriteData();
		size = __Size2();
	}

	//Loads all sprite data into 2D arrays
	//Also resets all previously set variables
	__EngineErrors __Sprite::Load(const __Location & loc)
	{
		Init();
		location = loc;

		std::vector<unsigned char> spriteFileBytes;
		std::wstring spriteFileLine;

		//Change file location
		if (YOL_ENGINE_DEBUG)
			location = __Location("EngineCoreRaw/" + std::string(loc.filePath, 11, loc.filePath.size() - 11));

		//Open menu file and get all bytes
		std::ifstream spriteFileIn(location.filePath, std::ios::binary);
		if (spriteFileIn.fail())
			return FILE_STREAM_ERROR;

		ReadFileBytes(spriteFileIn, spriteFileBytes);
		spriteFileIn.close();

		//Engine is in release mode - require deobfuscation
		if (!YOL_ENGINE_DEBUG)
			spriteFileBytes = DeobfuscateBytes(spriteFileBytes, project->GetProjectKey());

		//Set width and height of the sprite
		size.width = spriteFileBytes[0];
		size.height = spriteFileBytes[1];

		name = std::wstring(loc.fileName.begin(), loc.fileName.end());

		//Ignore empty file
		if (size.width != 0 && size.height != 0)
		{
			//Resize sprite vectors and make them transparent
			data.foregroundColor.resize(size.height, std::vector<__ConsoleColor>(size.width, cTransparent));
			data.backgroundColor.resize(size.height, std::vector<__ConsoleColor>(size.width, cTransparent));
			data.character.resize(size.height, std::vector<wchar_t>(size.width, 0xFF));

			//Read all bytes that are left in the file
			for (int i = 0, byteReadOffset = 2; i < size.height; i++)
			{
				for (int j = 0; j < size.width; j++, byteReadOffset++)
				{
					//Check if pixel is transparent (character == 0xFF, color = 0xFF)
					if (spriteFileBytes[byteReadOffset] == 0xFF &&
						spriteFileBytes[byteReadOffset + 1] == 0x00 &&
						spriteFileBytes[byteReadOffset + 2] == 0xFF)
						continue;

					//Read and store four pixel bytes
					data.foregroundColor[i][j] = static_cast<__ConsoleColor>(spriteFileBytes[byteReadOffset]/16);
					data.backgroundColor[i][j] = static_cast<__ConsoleColor>(spriteFileBytes[byteReadOffset]%16);
					data.character[i][j] = spriteFileBytes[(byteReadOffset+=2)-1] * 256 +spriteFileBytes[byteReadOffset];
				}
			}
		}

		//Obfuscate menu file in the EngineCore directory
		std::ofstream spriteFileOut(loc.path + "/" + loc.fileName + ".ytf", std::ios::binary);
		if (spriteFileOut.fail())
			return FILE_STREAM_ERROR;

		spriteFileBytes = ObfuscateBytes(spriteFileBytes, project->GetProjectKey());
		WriteFileBytes(spriteFileOut, spriteFileBytes);

		return SUCCESS;
	}

	//Draws the sprite in the specified position
	//If drawAlpha is set to true - transparent pixels of the sprite
	//will be drawn as following: cBlack foreground, cDarkGray background, 'x' character
	void __Sprite::Draw(const __Vec2 & pos, bool drawAlpha)
	{
		for (int i = 0; i < size.height; i++)
		{
			for (int j = 0; j < size.width; j++)
			{
				GotoXY(pos.x + j, pos.y + i);

				//Check that pixel is not transparent and that it is possible to print it
				if (data.backgroundColor[i][j] != cTransparent && data.foregroundColor[i][j] != cTransparent
					&& data.character[i][j] > 0x1F && data.character[i][j] != 0xFF)
					SetColor(data.foregroundColor[i][j], data.backgroundColor[i][j]);
				else if (drawAlpha) 
					SetColor(cBlack, cLightGray);

				std::wcout << data.character[i][j];
			}
		}

		SetColor(project->textColor, project->backgroundColor);
		GotoXY(0, 0);
	}
}