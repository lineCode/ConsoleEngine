/* Project.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This is the main part of any application developed with YOLConsoleEngine.
__Project class is responsible for controlling console window looks,
loading settings, keeping global encryption key, switching between
debug and release configuration and many more.

Basic usage:
	__Project Game(__Location("ProjectSettings.ytf"), "My_Encryption_Key");
This line of code will automatically load settings from 
"ProjectSettings.ytf" file and configure console window. 

Please read documentation for proper settingss file formatting

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	//Keeps track if __Project object already exists or not
	bool __Project::doesExist = false;
	
	//Initializes all directories, settings, and other project related stuff
	__Project::__Project(const __Location & loc, const std::wstring & key)
	{
		Init();
		//There can be only one!
		if (doesExist)
		{
			WarningMsg(L"There can be only one Project object in the entire program.\n");
			system("pause");
			exit(-1);
		}

		//Worse than "12345" or "password"
		if (key.empty())
		{
			WarningMsg(L"You can't use this global project key.\n");
			system("pause");
			exit(-1);
		}

		projectKey = key;

		//Sets keyboard layout to English (for proper _getch() work)
		PostMessage(GetForegroundWindow(), WM_INPUTLANGCHANGEREQUEST, INPUTLANGCHANGE_SYSCHARSET, 0x00000409);

		//Ban windows resizing
		SetWindowLongPtr(GetConsoleWindow(), GWL_STYLE, GetWindowLong(GetConsoleWindow(), GWL_STYLE)&~WS_SIZEBOX);

		//Sets proper encoding for console output
		SetConsoleCP(CP_UTF8);
		SetConsoleOutputCP(CP_UTF8);
		_setmode(_fileno(stdout), _O_U16TEXT);

		//Creates engine directories
		if (YOL_ENGINE_DEBUG)
		{
			CreateDirectoryW(L"EngineCoreRaw", NULL);
			CreateDirectoryW(L"EngineCoreRaw/UI", NULL);
			CreateDirectoryW(L"EngineCoreRaw/UI/Forms", NULL);
			CreateDirectoryW(L"EngineCoreRaw/UI/Menus", NULL);
			CreateDirectoryW(L"EngineCoreRaw/Sprites", NULL);
		}
		CreateDirectoryW(L"EngineCore", NULL);
		CreateDirectoryW(L"EngineCore/UI", NULL);
		CreateDirectoryW(L"EngineCore/UI/Forms", NULL);
		CreateDirectoryW(L"EngineCore/UI/Menus", NULL);
		CreateDirectoryW(L"EngineCore/Fonts", NULL);
		CreateDirectoryW(L"EngineCore/Sprites", NULL);

		//Loads project settings from file
		LoadSettingsFromFile(loc);

		//And the winner is you
		doesExist = true;
	}

	__Project::~__Project() 
	{
		//Free font
		RemoveFontResourceW((L"EngineCore/Fonts/" + defaultSettings.fontName + L".ttf").c_str());
	}

	//Initializes all variables
	void __Project::Init()
	{
		projectKey = std::wstring();
		location = __Location();
		defaultSettings = __ProjectSettings();
		textColor = defaultSettings.textColor;
		backgroundColor = defaultSettings.backgroundColor;
		size = defaultSettings.size;
		scrollbarVisible = defaultSettings.scrollbarVisible;
		gameSpeed = defaultSettings.gameSpeed;
		position = defaultSettings.position;
		fontSize = defaultSettings.fontSize;
		fontName = defaultSettings.fontName;
		isFullscreen = defaultSettings.isFullscreen;
		windowName = defaultSettings.windowName;
		windowControlsVisible = defaultSettings.windowControlsVisible;
	}

	//Parses settings file and applies wanted changes
	__EngineErrors __Project::LoadSettingsFromFile(const __Location & loc)
	{
		std::wstringstream settingsFileStream;
		std::vector<unsigned char> settingsFileBytes;
		std::wstring settingsFileLine;

		//Change file location
		if (YOL_ENGINE_DEBUG)
			location = __Location(L"EngineCoreRaw/" + std::wstring(loc.filePath, 11, loc.filePath.size() - 14) + L"txt");

		//Open menu file and get all bytes
		std::ifstream settingsFileIn(location.filePath, std::ios::binary);
		if (settingsFileIn.fail())
			return FILE_STREAM_ERROR;

		ReadFileBytes(settingsFileIn, settingsFileBytes);
		settingsFileIn.close();

		//Engine is in release mode - require deobfuscation
		if (!YOL_ENGINE_DEBUG)
			settingsFileBytes = DeobfuscateBytes(settingsFileBytes, projectKey);

		//File bytes are directly turned into wstringstream
		BytesToWSS(settingsFileBytes, settingsFileStream);

		//Parse settings file and set engine variables
		while (!settingsFileStream.eof())
		{
			getline(settingsFileStream, settingsFileLine);

			//Skip empty lines
			if (settingsFileLine.empty())
				continue;

			//Assigns the names and values of the settings
			std::wstring settingName(settingsFileLine, 0, settingsFileLine.find('='));
			std::wstring settingValue(settingsFileLine, settingsFileLine.find('=') + 1,
				settingsFileLine.size() - 2 - settingsFileLine.find('='));

			//Detect what setting is on this line and assign a proper value to the proper variable
			if (settingName == L"TextColor")
				defaultSettings.textColor = static_cast<__ConsoleColor>(_wtoi(settingValue.c_str()));
			else if (settingName == L"BackgroundColor")
				defaultSettings.backgroundColor = static_cast<__ConsoleColor>(_wtoi(settingValue.c_str()));
			else if (settingName == L"GameSpeed")
				defaultSettings.gameSpeed = _wtoi(settingValue.c_str());
			else if (settingName == L"Width")
				defaultSettings.size.width = _wtoi(settingValue.c_str());
			else if (settingName == L"Height")
				defaultSettings.size.height = _wtoi(settingValue.c_str());
			else if (settingName == L"ScrollbarVisible")
				defaultSettings.scrollbarVisible = static_cast<bool>(_wtoi(settingValue.c_str()));
			else if (settingName == L"PosX")
				defaultSettings.position.x = _wtoi(settingValue.c_str());
			else if (settingName == L"PosY")
				defaultSettings.position.y = _wtoi(settingValue.c_str());
			else if (settingName == L"FontSizeWidth")
				defaultSettings.fontSize.width = _wtoi(settingValue.c_str());
			else if (settingName == L"FontSizeHeight")
				defaultSettings.fontSize.height = _wtoi(settingValue.c_str());
			else if (settingName == L"FontName")
				defaultSettings.fontName = settingValue;
			else if (settingName == L"IsFullscreen")
				defaultSettings.isFullscreen = static_cast<bool>(_wtoi(settingValue.c_str()));
			else if (settingName == L"WindowName")
				defaultSettings.windowName = settingValue;
			else if (settingName == L"WindowControlsVisible")
				defaultSettings.windowControlsVisible = static_cast<bool>(_wtoi(settingValue.c_str()));
			else if (settingName == L"NewDir")
				CreateDirectoryW(settingValue.c_str(), NULL);
		}

		//Obfuscate project settings file in the EngineCore directory
		std::ofstream settingsFileOut(loc.path + L"/" + loc.fileName + L".ytf", std::ios::binary);
		if (settingsFileOut.fail())
			return FILE_STREAM_ERROR;

		WriteFileBytes(settingsFileOut, ObfuscateBytes(settingsFileBytes, projectKey));

		//Sets console look to default
		ResetAll();

		return SUCCESS;
	}

	//Resets current colors to default
	void __Project::ResetColors(const bool & update)
	{
		textColor = defaultSettings.textColor;
		backgroundColor = defaultSettings.backgroundColor;

		if (update)
			SetColor(textColor, backgroundColor);
	}

	//Resets current size and scrollbar to default
	void __Project::ResetSize(const bool & update)
	{
		size = defaultSettings.size;
		scrollbarVisible = defaultSettings.scrollbarVisible;

		if (update)
			SetConsoleWindowSize(size.width, size.height, scrollbarVisible);
	}

	//Resets current position to default
	void __Project::ResetPosition(const bool & update)
	{
		position = defaultSettings.position;

		if (update)
			SetWindowPos(GetConsoleWindow(), HWND_TOP, position.x, position.y, 0, 0, SWP_DRAWFRAME | SWP_NOSIZE | SWP_SHOWWINDOW);

		//TODO also redraw background fully, once layer system is supported
	}

	//Resets current font to default
	void __Project::ResetFont(const bool & update)
	{
		fontName = defaultSettings.fontName;
		fontSize = defaultSettings.fontSize;

		if (update)
		{
			CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
			GetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &font);
			AddFontResourceW((L"EngineCore/Fonts/" + defaultSettings.fontName + L".ttf").c_str());
			wcscpy_s(font.FaceName, defaultSettings.fontName.c_str());
			font.dwFontSize.X = defaultSettings.GetFontSize().Width();
			font.dwFontSize.Y = defaultSettings.GetFontSize().Height();
			SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &font);
		}
	}

	//Resets current screen display to default
	void __Project::ResetFullscreen(const bool & update)
	{
		isFullscreen = defaultSettings.isFullscreen;

		if (update)
			SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE),
				isFullscreen ? CONSOLE_FULLSCREEN_MODE : CONSOLE_WINDOWED_MODE, 0);
	}

	//Resets current display of control buttons to default
	void __Project::ResetWindowStyle(const bool & update)
	{
		windowControlsVisible = defaultSettings.windowControlsVisible;

		if (update)
		{
			LONG_PTR style = GetWindowLongPtr(GetConsoleWindow(), GWL_STYLE);
			SetWindowLongPtr(GetConsoleWindow(), GWL_STYLE,
				windowControlsVisible ? style : style & ~WS_SYSMENU);
		}
	}

	//Resets everything
	void __Project::ResetAll(const bool & update)
	{
		ResetFullscreen(update);
		ResetPosition(update);
		ResetColors(update);
		ResetWindowStyle(update);
		ResetFont(update);
		ResetSize(update);

		if (update)
			SetConsoleTitleW(defaultSettings.windowName.c_str());
	}

	//Prints success message in green text
	void __Project::SuccessMsg(const std::wstring & text)
	{
		SetColor(cLightGreen, backgroundColor);
		std::wcout << text;
		OutputDebugStringW((L"--SUCCESS: " + text + L"\n").c_str());
		SetColor(textColor, backgroundColor);
	}

	//Prints warning message in red text
	void __Project::WarningMsg(const std::wstring & text)
	{
		SetColor(cLightRed, backgroundColor);
		std::wcout << text;
		OutputDebugStringW((L"--WARNING: " + text + L"\n").c_str());
		SetColor(textColor, backgroundColor);
	}
}