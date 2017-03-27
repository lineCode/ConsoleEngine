/* YOLConsoleEngineMain.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This file connects all the modules of the YOLConsoleEngine in one place,
so in your project you can just do:
	#include "YOLConsoleEngineMain.h"
to get access to all YOLConsoleEngine features.

This file also contains some YOLConsoleEngine configurations, which you should
check out before starting a project

TODO in menu and forms change ACTIVE/SELECTED color/text to HOVER
TODO after font load and unload call the SendMessage function and send a WM_FONTCHANGE message to all top-level windows in the system

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/

/*
Since there is no actual docs right now I'm going to write very important engine mechanics here


*/

#ifndef YOL_CONSOLE_ENGINE_MAIN_H
#define YOL_CONSOLE_ENGINE_MAIN_H

//Regulation defines for compiling and using YOLConsoleEngine as a DYNAMIC library
#ifdef _WIN32
	#ifdef YOL_ENGINE_EXPORTS
		#define YOL_ENGINE_API extern "C" __declspec(dllexport)
	#else
		#define YOL_ENGINE_API extern "C" __declspec(dllimport)
	#endif
#else
	#define YOL_ENGINE_API 
#endif

//Engine configurations
//
//If defined to true, unobfuscated resources from "EngineCoreRaw" folder will be copied
//over to normal "EngineCore" directories, used, and obfuscated after load. 
//Overwise - obfuscated resources from "EngineCore" directories are used
//
//NOTE 1: this setting automatically adds "EngineCoreRaw/" prefix to all
//your __Location(path) objects, so the resulting filepath is (L"EngineCoreRaw/" + path + L".txt")
//
//NOTE 2: this setting does not apply to files that are never obfuscated by the engine (eg. fonts).
//Those files use "EngineCore" directory by default (eg "EngineCore/Fonts/font.ttf")
#define YOL_ENGINE_DEBUG true


//System includes
#ifdef __linux__
	#include <signal.h>					//Handles different terminal signals
	#include <termios.h>				//Provides replacement for _getch();
	#include <unistd.h>					//Provides replacement for _getch();
	
	//Linux systems require this defines to overwrite many of Windows' behaviours
	#define VK_TAB 0x09
	#define VK_RETURN 0x0D
	#define VK_BACK 0x7F
	#define OutputDebugStringW(a) {}
	#define CreateDirectory(name, value) mkdir(name, ACCESSPERMS)
#else
	#include <io.h>							//UTF8 console output support
	#include <Windows.h>				//Lots of good stuff
#endif

#include <fcntl.h>						//UTF8 console output support
#include <iostream>						//Console output streams
#include <string>							//String types
#include <fstream>						//File I/O
#include <sstream>						//Stream operations
#include <sys/stat.h> 				//Filesystem manipulations
#include <vector>							//Dynamic arrays 
#include <random>							//mt19937 PRNG
#include <memory>							//Smart pointers

//Engine includes
#include "YOLF.h"             //Core functions used in the YOLConsoleEngine
#include "BasicTypes.h"       //Basic types and manipulations with them (__Size2, __Vec2, __EngineErrors)
#include "Location.h"         //More convient way to store data of file location in the filesystem
#include "ProjectSettings.h"  //Default settings for the Project class
#include "Project.h"          //Project object for controlling various project settings
#include "Menu.h"
#include "Sprite.h"
#include "Form.h"
#include "FormInput.h"
#include "InputText.h"
#include "InputNumber.h"
#include "InputButton.h"

#endif