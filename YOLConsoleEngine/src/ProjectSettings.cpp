/* ProjectSettings.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	//Constructor defaults values to engine defaults
	__ProjectSettings::__ProjectSettings()
	{
		Reset();
	}

	__ProjectSettings::~__ProjectSettings() {}

	//Resets settings loaded from file to engine default settings
	void __ProjectSettings::Reset()
	{
		projectKey = std::wstring();
		location = __Location();

		textColor = cLightGray;
		backgroundColor = cBlack;
		size = __Size2(80, 25);
		scrollbarVisible = false;
		gameSpeed = 30;
		position = __Vec2(7, 0);
		fontSize = __Size2(8, 12);
		fontName = L"Consolas";
		isFullscreen = false;
		windowName = std::wstring();
		windowControlsVisible = true;
	}
}