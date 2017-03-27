/* Location.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This class provides a convient way to store information about specified file.
THis information includes:
-File extension
-File name
-Relative path
-Full file path

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	//Information defaults to empty/unspecified
	__Location::__Location()
	{
		Init();
	}

	//Gathers information about the file and stores it
	__Location::__Location(const std::string & filepath)
	{
		Init();

		//Get full path, name, extension
		//Safe to use if file does not exist
		if (!filepath.empty())
		{
			//TODO meh
			fileName = filepath.substr(filepath.find_last_of("/\\") + 1);
			fileName= fileName.substr(0, fileName.find_last_of(L'.'));


			filePath = filepath;
			filePathFull = GetFilePath(filepath);
			path = filePath.substr(0, filePath.find_last_of("\\/"));
			
			//Redo manually.
			//File name = from last / (or \\) to last .
			//file ext = from last . to end
			//fileName = fName;
			//fileExt.assign(fExt, 1, sizeof(fExt) - 1);
			
		}
	}

	__Location::~__Location() {}

	//Initializes all variables
	void __Location::Init()
	{
		fileExt = std::string();
		fileName = std::string();
		filePath = std::string();
		filePathFull = std::string();
		path = std::string();
	}
}