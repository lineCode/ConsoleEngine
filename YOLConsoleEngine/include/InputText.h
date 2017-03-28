/* Text.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

TEXT INPUT FIELD for YOLConsoleEngine Forms
Allows to set input field that supports user's string input

TEXT INPUT FORMAT
"INPUT_TEXT <x> <y> <textCol> <bgCol> <tipTextCol> <inputWidth> <tip> <val>"

INPUT_TEXT - type of the input
<x> and <y> - integer, specified input field position relative to Form X and Y
<textCol>, <bgCol>, <tipTextCol> - integer, values from __ConsoleColor enum that specify text color, background color and
tip text color respectively
<inputWidth> - interger, width of the text input field
<tip> - string, tip text (leave as "" for no tip)
<val> - string, value text (leave as "" for no value)

eg. "INPUT_TEXT 5 5 0 7 8 15 "HEY I'M A TIP" "VALUE WILL DISPLAY INSTEAD OF TIP""

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/

#ifndef YOL_CONSOLE_ENGINE_FORM_INPUT_TEXT_H
#define YOL_CONSOLE_ENGINE_FORM_INPUT_TEXT_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __InputText : public __FormInput
	{
	public:
		//Init constructor
		__InputText(const std::shared_ptr<__Project> & pr);

		//Init constructor with parsing input settings
		__InputText(const std::shared_ptr<__Project>& pr, const std::wstring & data);

		~__InputText();

		//Parses passed string to set up input field settings
		__EngineErrors ParseInputData(const std::wstring & data);

		//Statically displays text input field on the screen
		void Draw(const __Vec2 & ref);
		
		//Updates data based on input
		void Update(const int & keycode, const __Vec2 & ref);

		//Returns the type of input
		inline std::wstring GetType() { return inputType; }


		//Width of the input field
		unsigned int fieldWidth;

		//Tip for the input field
		std::wstring tip;

		//Tip text color
		__ConsoleColor tipTextColor;

	private:
		//Initializes all variables
		void Init();
	};
}

#endif