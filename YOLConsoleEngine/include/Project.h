/* Project.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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

TODO move ProjectSettins to this file
TODO maybe posX and posY relative from screen center?

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_PROJECT_H
#define YOL_CONSOLE_ENGINE_PROJECT_H

//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __Project
	{
	public:
		//Initializes all directories, settings, and other project related stuff
		__Project(const __Location & loc, const std::wstring & key);

		~__Project();

		//Returns default console settings loaded from file
		inline __ProjectSettings & GetDefaultSettings() { return defaultSettings; }

		//Returns project settings file location
		inline __Location GetLocation() { return location; }

		//Returns global encryption key
		inline std::wstring GetProjectKey() { return projectKey;  }

		//Resets current colors to default
		void ResetColors(const bool & update = true);

		//Resets current size and scrollbar to default
		void ResetSize(const bool & update = true);

		#ifdef _WIN32
			//Resets current position to default
			void ResetPosition(const bool & update = true);

			//Resets current font to default
			void ResetFont(const bool & update = true);

			//Resets current screen display to default
			void ResetFullscreen(const bool & update = true);

			//Resets current display of control buttons to default
			void ResetWindowStyle(const bool & update = true);
		#endif

		//Resets every current setting to default
		void ResetAll(const bool & update = true);

		//Prints success message in green text
		void SuccessMsg(const std::wstring & text);

		//Prints warning message in red text
		void WarningMsg(const std::wstring & text);


		//Current console text color
		__ConsoleColor textColor;

		//Current console background color
		__ConsoleColor backgroundColor;

		//Current console window size
		__Size2 size;

		//Current console scrollbar visibility
		bool scrollbarVisible;

		//Current speed of the game (FPS)
		unsigned int gameSpeed;

		//Current console X and Y positions
		__Vec2 position;

		//Current console font size
		__Size2 fontSize;

		//Current console font name
		std::wstring fontName;

		//Current console display mode
		bool isFullscreen;

		//Current console window name
		std::wstring windowName;

		//Current console window visibility of control buttons at the title bar
		bool windowControlsVisible;

	private:
		//Ban copy/assign constructor/operator
		__Project(const __Project & other);
		__Project & operator=(const __Project & other) = delete;

		//Parses settings file and applies wanted changes
		//Also sets default project settings to the values grabbed from file
		__EngineErrors LoadSettingsFromFile(const __Location & loc);

		//Initializes all variables
		void Init();


		//Global encryption key
		std::wstring projectKey;

		//Project settings file location
		__Location location; 

		//Keeps track if Project object already exists or not
		static bool doesExist;

		//Default console settings loaded from file
		__ProjectSettings defaultSettings;

		#ifdef __linux__
			//Signal handler for terminal resize 
			static void OnWindowResize(int signal);

			//Reference to self to handle signals statically
			static __Project * selfReference;
		#endif
	};
}


#endif