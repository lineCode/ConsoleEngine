/* InputText.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Init constructor
	__InputText::__InputText(const std::shared_ptr<__Project> & pr)
	{
		project = pr;
		Init();
	}

	//Init constructor with parsing input settings
	__InputText::__InputText(const std::shared_ptr<__Project> & pr, const std::wstring & data)
	{
		project = pr;
		//Init() is called in ParseInputData()
		ParseInputData(data);
	}

	__InputText::~__InputText() { }

	//Initializes all variables
	void __InputText::Init()
	{
		position = __Vec2();
		textColor = project->backgroundColor;
		backgroundColor = project->textColor;
		tipTextColor = textColor;
		inputType = L"INPUT_TEXT";
		fieldWidth = 10;
		data = std::wstring();
		defaultData = std::wstring();
		tip = std::wstring();
	}

	//Parses passed string to set up input field settings
	__EngineErrors __InputText::ParseInputData(const std::wstring & data)
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

		//Store three colors in the buffer since they first need to be
		//converted to __ConsolerColor
		int colorsTemp[3];
		dataStream >> colorsTemp[0] >> colorsTemp[1] >> colorsTemp[2];
		
		dataStream >> fieldWidth;

		//Set colors
		textColor = static_cast<__ConsoleColor>(colorsTemp[0]);
		backgroundColor = static_cast<__ConsoleColor>(colorsTemp[1]);
		tipTextColor = static_cast<__ConsoleColor>(colorsTemp[2]);

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
		
		//Assign default and tip values AND limit them
		tip.assign(data, quotesPos[0] + 1, quotesPos[1] - quotesPos[0] - 1);
		tip.assign(tip, 0, fieldWidth - 1);

		//Set and store default data
		defaultData.assign(data, quotesPos[2] + 1, quotesPos[3] - quotesPos[2] - 1);
		this->data = defaultData;

		return SUCCESS;
	}

	//Statically displays text input field on the screen
	void __InputText::Draw(const __Vec2 & ref)
	{
		SetColor(textColor, backgroundColor);
		GotoXY(ref.x + position.x, ref.y + position.y);

		//(Re)Draw background of input field
		for (int i = 0; i < fieldWidth; i++)
			std::wcout << " ";
		GotoXY(ref.x + position.x, ref.y + position.y);

		//If there is any data - display it
		if (data.size() > 0)
		{
			if (data.size() < fieldWidth)
				std::wcout << data;
			else //cut data since it can't fit in one fieldWidth width
				std::wcout << std::wstring(data, data.size() - fieldWidth + 1, fieldWidth - 1);
		}
		else if (tip.size() > 0) //display tip if available
		{
			SetColor(tipTextColor, backgroundColor);
			std::wcout << tip;
			GotoXY(ref.x + position.x, ref.y + position.y);
		}
	}

	//Updates data based on input
	void __InputText::Update(const int & keycode, const __Vec2 & ref)
	{
		if (keycode == VK_BACK && data.size() > 0)
		{
			data.pop_back();
			Draw(ref);
		}
		else if (keycode != VK_BACK && keycode > 31)
		{
			data.push_back((wchar_t)keycode);
			Draw(ref);
		}
	}
}