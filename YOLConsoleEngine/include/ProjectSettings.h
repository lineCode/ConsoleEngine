/* ProjectSettings.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This header provides an access to the __ProjectSettings structure which is used in
the __Project object to keep track of the project settings
Settings are loaded and can only be modified during __Project construction
If for some reason you want to ignore settings loaded from file - use __ProjectSettings::Reset()
to revert loaded settings to engine defaults

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_PROJECT_SETTINGS_H
#define YOL_CONSOLE_ENGINE_PROJECT_SETTINGS_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __ProjectSettings
	{
		friend class __Project;
	public:
		//Get methods for accessing readd-only data
		inline std::wstring GetProjectKey() { return projectKey; }
		inline __Location GetLocation() { return location; }
		inline __ConsoleColor GetTextColor() { return textColor; }
		inline __ConsoleColor GetBackgroundColor() { return backgroundColor; }
		inline __Size2 GetSize() { return size; }
		inline bool GetScrollbar() { return scrollbarVisible; }
		inline __Vec2 GetPosition() { return position; }
		inline unsigned int GetGameSpeed() { return gameSpeed; }
		inline __Size2 GetFontSize() { return fontSize; }
		inline std::wstring GetFontName() { return fontName; }
		inline bool GetIsFullscreen() { return isFullscreen; }
		inline std::wstring GetWindowName() { return windowName; }
		inline bool GetWindowControls() { return windowControlsVisible; }

		//Resets settings loaded from file to engine default settings
		void Reset();

	private:
		//Constructor defaults values to engine defaults
		__ProjectSettings();

		~__ProjectSettings();

		//Global encryption key
		std::wstring projectKey;

		//Project settings file location
		__Location location;

		//Console text color
		__ConsoleColor textColor;

		//Console background color
		__ConsoleColor backgroundColor;

		//Console window size
		__Size2 size;

		//Console scrollbar visibility
		bool scrollbarVisible;

		//Speed of the game (FPS)
		unsigned int gameSpeed;

		//Console X and Y positions
		__Vec2 position;

		//Console font size
		__Size2 fontSize;

		//Console font name
		std::wstring fontName;

		//Console display mode
		bool isFullscreen;

		//Console window name
		std::wstring windowName;

		//Console window control buttons at the title bar visibility
		bool windowControlsVisible;

	};
}
#endif