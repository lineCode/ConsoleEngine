/* Menu.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This part of YOLConsoleEngine allows for easy menu creation/control

Basic usage:
	__Menu mn(&Game, __Location("UI/Menus/menu.ymf"));
	mn.Draw();
This code loads the menu from menu file and only displays it on the screen

For menu file format and code examples read documentation

TODO: -Store menu size in __Size2

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_MENU_H
#define YOL_CONSOLE_ENGINE_MENU_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Holds data about specific menu item (used in the menu option vector)
	//Allows to edit the contents of each menu option
	struct __MenuItem
	{
		friend class __Menu;
	public:
		//Constructs __MenuItem with default option colors from __Project object
		__MenuItem(const std::shared_ptr<__Project> & pr)
		{
			position = __Vec2();
			normalText = std::wstring();
			activeText = std::wstring();
			normalTextColor = pr->textColor;
			normalBackgroundColor = pr->backgroundColor;
			activeTextColor = pr->backgroundColor;
			activeBackgroundColor = pr->textColor;
			id = -1;
		}

		//Returns option id
		inline int GetId() { return id; }


		//Menu item position relative to __Menu position and anchor
		__Vec2 position;

		//Normal text
		std::wstring normalText;

		//Highlighted text
		std::wstring activeText;

		//Text color of normal option
		__ConsoleColor normalTextColor;

		//Background color of normal option
		__ConsoleColor normalBackgroundColor;

		//Text color of highlighted option
		__ConsoleColor activeTextColor;

		//Background color of highlighted option
		__ConsoleColor activeBackgroundColor;

	private:
		//Option id. No actual purpose
		int id;
	};


	///////////////////
	//
	//Menu class
	//
	///////////////////
	class YOL_ENGINE_API __Menu
	{	
		friend class __Project;
	public:

		//Constructor without menu file load
		__Menu(const std::shared_ptr<__Project> & pr);

		//Constructor with menu file load
		__Menu(const std::shared_ptr<__Project> & pr, const __Location & loc);

		~__Menu();

		//Loads all components of the menu from given file
		//Also resets all previously set variables
		__EngineErrors Load(const __Location & loc);

		//Statically displays menu on the screen
		void Draw();

		//Updates menu based on input
		//Returns current active item
		int Update(int keycode);
		
		//Returns menu file location
		inline __Location GetLocation() { return location; }

		//Returns current active item number
		inline int GetCurrentActiveItem() { return currentActiveItem; }
		
		//Sets current highlighted item
		//void SetCurrentActiveItem() {}


		//Menu controlled vertically or horizontally
		enum __ControlDirection
		{
			CONTROL_HORIZONTAL,
			CONTROL_VERTICAL,
		};

		//Menu controlled by arrows or WASD
		enum __ControlKeys
		{
			ARROW_KEYS,
			WASD_KEYS,
		};

		//Name of the menu. No actual purpose
		std::wstring name;

		//Stores menu position TEMPORARY, UNTIL LAYERS ARE IMPLEMENTED
		__Vec2 position;

		//In which direction menu is controlled
		__ControlDirection controlDirection;

		//Key types to control menu
		__ControlKeys controlKeys;

		//Array of menu items
		std::vector<__MenuItem> item;

	private:
		//Initializes all variables
		void Init();

		//Increse active item
		void NextItem();

		//Decrese active item
		void PrevItem();


		//Reference to the __Project object
		std::shared_ptr<__Project> project;

		//Paths to the menu file
		__Location location;

		//Current active item number
		int currentActiveItem;
	};
}

#endif