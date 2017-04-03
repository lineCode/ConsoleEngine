/* InputNumber.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

NUMBER INPUT FIELD for YOLConsoleEngine Forms
Allows to set input field that supports user's number input

NUMBER INPUT FORMAT
"INPUT_NUMBER <x> <y> <textCol> <bgCol> <tipTextCol> <inputWidth> <allowNegative> <allowFloat> <allowMultiple> <allowHex> <tip> <val>"

INPUT_NUMBER - type of the input
<x> and <y> - integer, specified input field position relative to Form X and Y
<textCol>, <bgCol>, <tipTextCol> - integer, values from __ConsoleColor enum that specify text color, background color and
tip text color respectively
<inputWidth> - interger, width of the number input field
<allowNegative> - bool, enables or disables '-' input character
<allowFloat> - bool, enables or disables '.' input character
<allowMultiple> - bool, enables or disables ' ' input character
<allowHex> - bool, enables or disables A-F inputs
<tip> - string, tip text (leave as "" for no tip)
<val> - string, value text (leave as "" for no value)

eg. "INPUT_NUMBER 5 5 0 7 8 15 1 0 0 "HEY I'M A TIP" "1337""

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/

#ifndef YOL_CONSOLE_ENGINE_FORM_INPUT_NUMBER_H
#define YOL_CONSOLE_ENGINE_FORM_INPUT_NUMBER_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __InputNumber : public __FormInput
	{
	public:
		//Init constructor
		__InputNumber(const std::shared_ptr<__Project> & pr);

		//Init constructor with parsing input settings
		__InputNumber(const std::shared_ptr<__Project>& pr, const std::wstring & data);

		~__InputNumber();

		//Parses passed string to set up input field settings
		__EngineErrors ParseInputData(const std::wstring & data);

		//Statically displays number input field on the screen
		void Draw(const __Vec2 & ref);
		
		//Updates data based on input
		void Update(const int & keycode, const __Vec2 & ref);

		//Returns the type of input
		inline std::wstring GetType() { return inputType; }


		//Width of the input field
		unsigned int fieldWidth;

		//Allows negative numbers ('-' char for input)
		bool allowNegative;

		//Allows float numbers (',' char for input)
		bool allowFloat;

		//Allows multiple numbers to be entered (' ' char for input)
		bool allowMultiple;

		//Allows to enter letters A-F
		bool allowHex;


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