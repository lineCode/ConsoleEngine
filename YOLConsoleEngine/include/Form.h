/* Form.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

Base system for HTML like forms for accepting user input.
Requires a file with instructions in UI/Forms directory

Check documentation of each input type for proper syntax

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_FORM_H
#define YOL_CONSOLE_ENGINE_FORM_H

//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	class __FormInput;

	class YOL_ENGINE_API __Form
	{
		friend class __Project;
	public:
		//Constructor without form file load
		__Form(const std::shared_ptr<__Project> & pr);

		//Constructor with form file load
		__Form(const std::shared_ptr<__Project> & pr, const __Location & loc);

		~__Form();

		//Loads all components of the form from given file
		//Also resets all previously set variables
		__EngineErrors Load(const __Location & loc);

		//Goes through each input field and calls Draw() method
		void Draw();

		//Updates form based on input
		//Returns current active input field
		int Update(const int & keycode);

		//Returns form file location
		inline __Location GetLocation() { return location; }

		//Returns current active input number
		inline int GetCurrentActiveInput() { return currentActiveInput; }


		//Name of the form. No actual purpose
		std::wstring name;

		//Stores form position TEMPORARY, UNTIL LAYERS ARE IMPLEMENTED
		__Vec2 position;

		//Key to go through form inputs backwards
		unsigned int keyBack;

		//Vector of all input fields
		//Has to be a pointer to avoid object slicing and
		//has to be shared to allow copy/assign
		std::vector<std::shared_ptr<__FormInput>> input;

	private:
		//Initializes all variables
		void Init();


		//Reference to the __Project object
		std::shared_ptr<__Project> project;

		//Paths to the form file
		__Location location;

		//Current active input number
		int currentActiveInput;
	};
}

#endif