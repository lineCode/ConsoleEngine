/* Menu.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This part of YOLConsoleEngine allows for easy menu creation/control

Basic usage:
__Menu mn(&Game, __Location("UI/Menus/menu.ymf"));
mn.Draw();
This code loads the menu from menu file and only displays it on the screen

For menu file format and code examples read documentation

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Constructor without menu file load
	__Menu::__Menu(const std::shared_ptr<__Project> & pr) : project(pr)
	{
		Init();
	}

	//Constructor with menu file load
	__Menu::__Menu(const std::shared_ptr<__Project> & pr, const __Location & loc) : project(pr)
	{
		//Init() is called in Load()
		Load(loc);
	}

	__Menu::~__Menu() { }

	//Initializes all variables
	void __Menu::Init()
	{
		location = __Location();
		currentActiveItem = 0;
		name = std::wstring();
		position = __Vec2();
		controlDirection = CONTROL_VERTICAL;
		controlKeys = ARROW_KEYS;
		item = std::vector<__MenuItem>();
	}

	//Loads all components of the menu from given file
	//Also resets all previously set variables
	__EngineErrors __Menu::Load(const __Location & loc)
	{
		Init();
		location = loc;

		std::wstringstream menuFileStream;
		std::vector<unsigned char> menuFileBytes;
		std::wstring menuFileLine;

		//Change file location
		if (YOL_ENGINE_DEBUG)
			location = __Location("EngineCoreRaw/" + std::string(loc.filePath, 11, loc.filePath.size() - 14) + "txt");

		//Open menu file and get all bytes
		std::ifstream menuFileIn(location.filePath, std::ios::binary);
		if (menuFileIn.fail())
			return FILE_STREAM_ERROR;

		ReadFileBytes(menuFileIn, menuFileBytes);
		menuFileIn.close();

		//Engine is in release mode - require deobfuscation
		if (!YOL_ENGINE_DEBUG)
			menuFileBytes = DeobfuscateBytes(menuFileBytes, project->GetProjectKey());

		//File bytes are directly turned into wstringstream
		BytesToWSS(menuFileBytes, menuFileStream);

		//Read menu information from first line
		//<menu name> <x> <y> 
		std::getline(menuFileStream, menuFileLine);
		std::wstringstream(menuFileLine) >> name >> position.x >> position.y;

		//By default controlDirection is CONTROL_VERTICAL so we 
		//only need to find HORIZONTAL to change it to CONTROL_HORIZONTAL
		if (menuFileLine.find(L"HORIZONTAL") != std::wstring::npos)
			controlDirection = CONTROL_HORIZONTAL;

		//By default controlKeys is ARROW_KEYS so we 
		//only need to find WASD to change it to WASD_KEYS
		if (menuFileLine.find(L"WASD") != std::wstring::npos)
			controlKeys = WASD_KEYS;

		//Parse through the rest of the file to get information about all options
		while (!menuFileStream.eof())
		{
			//Skip empty lines
			std::getline(menuFileStream, menuFileLine);
			if (menuFileLine.empty())
				continue;

			//Create temporary option object with an id
			__MenuItem tempItem(project);
			tempItem.id = item.size();

			//Get item X and Y position relative to menu anchor/position/rotation
			std::wstringstream(menuFileLine) >> tempItem.position.x >> tempItem.position.y;

			//Save positions of quotation marks for extracting option names later
			int quotesPos[4];
			for (int i = 0, x = 0; i < menuFileLine.size(); i++)
			{
				//Check if '"' is escaped
				if (menuFileLine[i] == '"' && menuFileLine[i - 1] != '\\')
				{
					quotesPos[x] = i;
					x++;
				}
			}

			//Set option names
			tempItem.activeText.assign(menuFileLine, quotesPos[2] + 1, quotesPos[3] - quotesPos[2] - 1);
			tempItem.normalText.assign(menuFileLine, quotesPos[0] + 1, quotesPos[1] - quotesPos[0] - 1);

			//Extract four colors and store them in a temporary buffer, since
			//we first have to convert them to __ConsoleColor
			int colorsTemp[4];
			std::wstringstream(std::wstring(menuFileLine, quotesPos[3] + 2, menuFileLine.size() - quotesPos[3] - 2))
				>> colorsTemp[0] >> colorsTemp[1] >> colorsTemp[2] >> colorsTemp[3];

			//Set option colors
			tempItem.normalTextColor = static_cast<__ConsoleColor>(colorsTemp[0]);
			tempItem.normalBackgroundColor = static_cast<__ConsoleColor>(colorsTemp[1]);
			tempItem.activeTextColor = static_cast<__ConsoleColor>(colorsTemp[2]);
			tempItem.activeBackgroundColor = static_cast<__ConsoleColor>(colorsTemp[3]);

			//Save option in the option array
			item.push_back(tempItem);
		}

		//Obfuscate menu file in the EngineCore directory
		std::ofstream menuFileOut(loc.path + "/" + loc.fileName + ".ytf", std::ios::binary);
		if (menuFileOut.fail())
			return FILE_STREAM_ERROR;

		menuFileBytes = ObfuscateBytes(menuFileBytes, project->GetProjectKey());
		WriteFileBytes(menuFileOut,menuFileBytes);

		//Do not allow menus with no options
		if (item.size() < 1)
			return FILE_EMPTY;

		return SUCCESS;
	}

	//Statically displays menu on the screen
	void __Menu::Draw()
	{
		//Loop through every menu item and draw it on required coords
		//with specified color and text
		for (int i = 0; i < item.size(); i++)
		{
			//TODO anchor point and rotation point
			GotoXY(nearbyint(item[i].position.x + position.x), nearbyint(item[i].position.y + position.y));

			//If this option is active, print it in active color
			if (i == currentActiveItem)
			{
				SetColor(item[i].activeTextColor, item[i].activeBackgroundColor);
				std::wcout << item[i].activeText;
			}
			else
			{
				SetColor(item[i].normalTextColor, item[i].normalBackgroundColor);
				std::wcout << item[i].normalText;
			}
		}

		SetColor(project->textColor, project->backgroundColor);
		GotoXY(0, 0);
	}

	//Updates menu based on input
	//Returns current active item
	int __Menu::Update(int keycode)
	{
		if(keycode == VK_ESCAPE_CHAR)
		{
			//On windows arrow hit sends VK_ESCAPE_CHAR and right after that - keycode for arrow key
			//So we need one step less
			keycode = _getwch();

			#ifdef __linux__
				//On arrow hit on linux _getwch() recieves three characters:
				//VK_ESCAPE_CHAR, '[', N, where N is a keycode for either 'A', 'B', 'C' or 'D'
				//We already cought VK_ESCAPE_CHAR, and skipped '[' now we get actual N
				keycode = _getwch();
			#endif
		}
		

		//Controls
		if (controlDirection == CONTROL_HORIZONTAL)
		{
			//left
			if ((controlKeys == ARROW_KEYS && keycode == VK_LEFT) ||
				(controlKeys == WASD_KEYS && keycode == 97))
				PrevItem();

			//right
			else if ((controlKeys == ARROW_KEYS && keycode == VK_RIGHT) ||
				(controlKeys == WASD_KEYS && keycode == 100))
				NextItem();
		}
		else
		{
			//up
			if ((controlKeys == ARROW_KEYS && keycode == VK_UP) ||
				(controlKeys == WASD_KEYS && keycode == 119))
				PrevItem();

			//down
			else if ((controlKeys == ARROW_KEYS && keycode == VK_DOWN) ||
				(controlKeys == WASD_KEYS && keycode == 115))
				NextItem();
		}

		SetColor(project->textColor, project->backgroundColor);
		GotoXY(0, 0);

		//Return id of current highlighted option
		return currentActiveItem;
	}

	//Increse active item
	void __Menu::NextItem()
	{
		//If no items left - check if menu allows wrap around and set to the 
		//first position
		if (currentActiveItem++ >= item.size()-1)
				currentActiveItem = 0;
		Draw();
	}

	//Decrease active item
	void __Menu::PrevItem()
	{
		//If no items left - check if menu allows wrap around and set to the 
		//last position
		if (currentActiveItem-- <= 0)
				currentActiveItem = item.size() - 1;
		Draw();
	}
}