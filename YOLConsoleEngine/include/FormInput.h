/* FormInput.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

A base class for every input field type.
Does not have any declared variables or methods.

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_FORM_INPUT_H
#define YOL_CONSOLE_ENGINE_FORM_INPUT_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __FormInput
	{
		friend class __Form;
	public: 
		//Statically displays input on the screen
		virtual void Draw(const __Vec2 & ref) { }

		//Updates data based on input
		virtual void Update(const int & keycode, const __Vec2 & ref) { }

		//Parses passed string to set up input field settings
		virtual __EngineErrors ParseInputData(const std::wstring & data) { return EMPTY_ERROR; }

		//Returns user input
		inline void GetData(std::wstring & outputBuf) { outputBuf = data; }

		//Returns default value of the input
		inline void GetDefaultData(std::wstring & outputBuf) { outputBuf = defaultData; }

		//Returns user input
		inline std::wstring GetData() { return data; }

		//Returns default value of the input
		inline std::wstring GetDefaultData() { return defaultData; }

		//Returns the type of input
		inline std::wstring GetType() { return inputType; }


		//Input position
		__Vec2 position;

		//Input text color
		__ConsoleColor textColor;

		//Input background color
		__ConsoleColor backgroundColor;

	protected:
		//Base of input field cannot be constructed
		__FormInput() { };

		//Reference to the __Project object
		std::shared_ptr<__Project> project;

		//Data entered
		std::wstring data;

		//Type of the input
		std::wstring inputType;

		//Default value
		std::wstring defaultData;
	};
}

#endif