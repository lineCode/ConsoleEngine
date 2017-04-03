/* InputFile.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

FILE INPUT FIELD for YOLConsoleEngine Forms
Allows to specify text string for file location

FILE INPUT FORMAT
"INPUT_FILE <x> <y> <textCol> <bgCol> <inputWidth> <allowMultiple> <filePrefix>"

INPUT_TEXT - type of the input
<x> and <y> - integer, specified input field position relative to Form X and Y
<textCol>, <bgCol> - integer, values from __ConsoleColor enum that specify text color and background color
<inputWidth> - interger, width of the text input field
<allowMultiple> - bool, enables or disables ',' input character
<filePrefix> - string, added at the start of every file path string

eg. "INPUT_FILE 5 5 0 7 15 0 "searchInThisFolder/""

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Init constructor
	__InputFile::__InputFile(const std::shared_ptr<__Project> & pr)
	{
		project = pr;
		Init();
	}

	//Init constructor with parsing input settings
	__InputFile::__InputFile(const std::shared_ptr<__Project> & pr, const std::wstring & data)
	{
		project = pr;
		//Init() is called in ParseInputData()
		ParseInputData(data);
	}

	__InputFile::~__InputFile() { }

	//Initializes all variables
	void __InputFile::Init()
	{
		position = __Vec2();
		textColor = project->backgroundColor;
		backgroundColor = project->textColor;
		inputType = L"INPUT_FILE";
		fieldWidth = 10;
		data = std::wstring();
		filePrefix = std::wstring();
		allowMultiple = false;
	}

	//Parses passed string to set up input field settings
	__EngineErrors __InputFile::ParseInputData(const std::wstring & data)
	{
		Init();
	
		std::wstring typeCheck;
		std::wstringstream dataStream(data);

		//Check that correct type settings are passed
		dataStream >> typeCheck;
		if (typeCheck != inputType)
			return WRONG_INPUT_TYPE;

		//Input field position relative to form's X and Y
		dataStream >> position.x >> position.y;

		//Store two colors in the buffer since they first need to be
		//converted to __ConsolerColor
		int colorsTemp[2];
		dataStream >> colorsTemp[0] >> colorsTemp[1];
		
		//Other settings
		dataStream >> fieldWidth >> allowMultiple;

		//Set colors
		textColor = static_cast<__ConsoleColor>(colorsTemp[0]);
		backgroundColor = static_cast<__ConsoleColor>(colorsTemp[1]);

		//Save positions of quotation marks for extracting tip and value values (hmmmm? value values)
		int quotesPos[2];
		for (int i = 0, x = 0; i < data.size(); i++)
		{
			//Check if '"' is escaped
			if (data[i] == '"' && data[i - 1] != '\\')
			{
				quotesPos[x] = i;
				x++;
			}
		}

		//Set and store file prefix
		filePrefix.assign(data, quotesPos[0] + 1, quotesPos[1] - quotesPos[0] - 1);

		//By default data should contain file prefix
		this->data = filePrefix;

		return SUCCESS;
	}

	//Statically displays text input field on the screen
	void __InputFile::Draw(const __Vec2 & ref)
	{
		SetColor(textColor, backgroundColor);
		GotoXY(ref.x + position.x, ref.y + position.y);

		//(Re)Draw background of input field
		for (int i = 0; i < fieldWidth; i++)
			std::wcout << " ";
		GotoXY(ref.x + position.x, ref.y + position.y);

		//If there is any data - display it
		if (data.size() < fieldWidth)
			std::wcout << data;
		else //cut data since it can't fit in one fieldWidth width
			std::wcout << std::wstring(data, data.size() - fieldWidth + 1, fieldWidth - 1);
	}

	//Updates data based on input
	void __InputFile::Update(const int & keycode, const __Vec2 & ref)
	{
		if (keycode == VK_BACK && data.size() > filePrefix.size())
		{
			//If backspace is pressed on filePrefix 
			if (data.rfind(filePrefix) == data.size() - filePrefix.size())
			{
				//Delete entire filePrefix but only if it is not a first one
				data.erase(data.size()- filePrefix.size() - 2, filePrefix.size()+2);
			}
			else
				data.pop_back();

			Draw(ref);
		}
		//Disallow commas unless allowed multiple files plus ignore all forbidden characters
		else if (keycode != VK_BACK && keycode > 31 && std::wstring(L"\\*:?\"<>|").find(keycode) == std::wstring::npos)
		{
			if (keycode == L',' && allowMultiple && data.back() != L' ' && data.back() != L',')
				data += L", " + filePrefix;
			else if (keycode != L',')
				data.push_back((wchar_t)keycode);

			Draw(ref);
		}
	}
}