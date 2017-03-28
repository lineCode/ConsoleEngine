/* Location.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This class provides a convient way to store information about specified file.
THis information includes:
	-File extension
	-File name
	-Relative file path
	-Full file path

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_LOCATION_H
#define YOL_CONSOLE_ENGINE_LOCATION_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __Location
	{
	public:
		//Information defaults to empty/unspecified
		__Location();

		//Gathers information about the file and stores it
		__Location(const std::string & filepath);

		~__Location();


		//File extension
		std::string fileExt;

		//File name
		std::string fileName;

		//Relative file path
		std::string filePath;

		//Full file path
		std::string filePathFull;

		//Only path to file, no ext or name
		std::string path;
				
	private:
		//Initializes all variables
		void Init();
	};
}
#endif