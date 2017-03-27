/* Button.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

Button input that returns the code specified code when submitted

BUTTON INPUT FORMAT
"INPUT_BUTTON <x> <y> <textCol> <bgCol> <hoverTextCol> <hoverBgCol> <code> <text>"

INPUT_BUTTON - type of the input
<x> and <y> - integer, specified input field position relative to Form X and Y
<textCol>, <bgCol>, <hoverTextCol>, <hoverBgCol> - integer, values from __ConsoleColor enum 
that specify text color, background color, hover text color and hover background color respectively
<code> - string, a numeric code that is returned on Form.Update() if VK_RETURN is hit
<text> - string, text displayed on the button

NOTE:
data - the code that is returned
defaultData - text of the button

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/

#ifndef YOL_CONSOLE_ENGINE_FORM_INPUT_BUTTON_H
#define YOL_CONSOLE_ENGINE_FORM_INPUT_BUTTON_H

//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __InputButton : public __FormInput
	{
	public:
		//Init constructor
		__InputButton(const std::shared_ptr<__Project> & pr);

		//Init constructor with parsing input settings
		__InputButton(const std::shared_ptr<__Project>& pr, const std::wstring & data);

		~__InputButton();

		//Parses passed string to set up input field settings
		__EngineErrors ParseInputData(const std::wstring & data);

		//Displays button on the screen
		void Draw(const __Vec2 & ref);
		
		//Updates data based on input
		void Update(const int & keycode, const __Vec2 & ref) { };

		//Returns the type of input
		inline std::wstring GetType() { return inputType; }


		//Hover text color
		__ConsoleColor hoverTextColor;

		//Hover background color
		__ConsoleColor hoverBackgroundColor;

	private:
		//Initializes all variables
		void Init();
	};
}

#endif