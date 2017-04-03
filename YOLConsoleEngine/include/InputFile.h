/* InputFile.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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

#ifndef YOL_CONSOLE_ENGINE_FORM_INPUT_FILE_H
#define YOL_CONSOLE_ENGINE_FORM_INPUT_FILE_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __InputFile : public __FormInput
	{
	public:
		//Init constructor
		__InputFile(const std::shared_ptr<__Project> & pr);

		//Init constructor with parsing input settings
		__InputFile(const std::shared_ptr<__Project>& pr, const std::wstring & data);

		~__InputFile();

		//Parses passed string to set up input field settings
		__EngineErrors ParseInputData(const std::wstring & data);

		//Statically displays text input field on the screen
		void Draw(const __Vec2 & ref);
		
		//Updates data based on input
		void Update(const int & keycode, const __Vec2 & ref);

		//Returns the type of input
		inline std::wstring GetType() { return inputType; }


		//Allows multiple files to be entered (' ' char for input)
		bool allowMultiple;

		//Width of the input field
		unsigned int fieldWidth;

		//Value for file prefix
		std::wstring filePrefix;

	private:
		//Initializes all variables
		void Init();
	};
}

#endif