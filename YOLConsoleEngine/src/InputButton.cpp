/* InputButton.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Init constructor
	__InputButton::__InputButton(const std::shared_ptr<__Project> & pr)
	{
		project = pr;
		Init();
	}

	//Init constructor with parsing input settings
	__InputButton::__InputButton(const std::shared_ptr<__Project> & pr, const std::wstring & data)
	{
		project = pr;
		//Init() is called in ParseInputData()
		ParseInputData(data);
	}

	__InputButton::~__InputButton() { }

	//Initializes all variables
	void __InputButton::Init()
	{
		position = __Vec2();
		textColor = project->backgroundColor;
		backgroundColor = project->textColor;
		hoverTextColor = backgroundColor;
		hoverBackgroundColor = textColor;
		inputType = L"INPUT_BUTTON";
		data = std::wstring();
		defaultData = std::wstring();
	}

	//Parses passed string to set up input field settings
	__EngineErrors __InputButton::ParseInputData(const std::wstring & data)
	{
		Init();

		std::wstring typeCheck;
		std::wstringstream dataStream(data);

		//Check that correct type settings are passed
		dataStream >> typeCheck;
		if (typeCheck != inputType)
			return WRONG_INPUT_TYPE;

		//Input field position relative to form's X and Y
		dataStream >> position.x >> position.y;

		//Store four colors in the buffer since they first need to be
		//converted to __ConsolerColor
		int colorsTemp[4];
		dataStream >> colorsTemp[0] >> colorsTemp[1] >> colorsTemp[2] >> colorsTemp[3];
		
		//Set colors
		textColor = static_cast<__ConsoleColor>(colorsTemp[0]);
		backgroundColor = static_cast<__ConsoleColor>(colorsTemp[1]);
		hoverTextColor = static_cast<__ConsoleColor>(colorsTemp[2]);
		hoverBackgroundColor = static_cast<__ConsoleColor>(colorsTemp[3]);

		//Save positions of quotation marks for extracting tip and value values (hmmmm? value values)
		int quotesPos[4];
		for (int i = 0, x = 0; i < data.size(); i++)
		{
			//Check if '"' is escaped
			if (data[i] == '"' && data[i - 1] != '\\')
			{
				quotesPos[x] = i;
				x++;
			}
		}
		
		//Assign return code
		this->data.assign(data, quotesPos[0] + 1, quotesPos[1] - quotesPos[0] - 1);

		//Assign button text
		defaultData.assign(data, quotesPos[2] + 1, quotesPos[3] - quotesPos[2] - 1);

		return SUCCESS;
	}

	//Displays button on the screen
	void __InputButton::Draw(const __Vec2 & ref)
	{
		//Dirty hack. If data last character is set to A
		//and then input button is drawn in active colors
		if (data.back() == L'A')
		{
			SetColor(hoverTextColor, hoverBackgroundColor);
			data.pop_back();
		}
		else
			SetColor(textColor, backgroundColor);
		GotoXY(ref.x + position.x, ref.y + position.y);
		
		std::wcout << defaultData;

		SetColor(project->textColor, project->backgroundColor);
		GotoXY(0, 0);
	}
}