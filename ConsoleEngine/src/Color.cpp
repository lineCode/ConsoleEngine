////////////////////////////////////////////////////////////////
//                                                            //
//      Colors.cpp                                            //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#include "../include/Color.h"

using namespace std;
using namespace ConsoleEngine;

// UD: Shorthand for writing Color(cRed, cRed)
const Color Color::red = Color(cRed, cRed);

// UD: Shorthand for writing Color(cGreen, cGreen)
const Color Color::green = Color(cGreen, cGreen);

// UD: Shorthand for writing Color(cBlue, cBlue)
const Color Color::blue = Color(cBlue, cBlue);

// UD: Shorthand for writing Color(cBlack, cBlack)
const Color Color::black = Color(cBlack, cBlack);

// UD: Shorthand for writing Color(cWhite, cWhite)
const Color Color::white = Color(cWhite, cWhite);

// UD: Shorthand for writing Color(cYellow, cYellow)
const Color Color::yellow = Color(cYellow, cYellow);

// UD: Shorthand for writing Color(cCyan, cCyan)
const Color Color::cyan = Color(cCyan, cCyan);

// UD: Shorthand for writing Color(cMagenta, cMagenta)
const Color Color::magenta = Color(cMagenta, cMagenta);

// UD: Shorthand for writing Color(cGray, cGray)
const Color Color::gray = Color(cGray, cGray);

// Returns grayscaled ConsoleColor
const ConsoleColor Color::GetGrayscaleColor(const ConsoleColor & color)
{
	switch (color)
	{
	case 0:
	case 1:
	case 4:
	case 5:
		return cBlack;

	case 2:
	case 3:
	case 8:
	case 9:
		return cGray;

	case 6:
	case 7:
	case 12:
	case 13:
		return cLightGray;

	case 10:
	case 11:
	case 14:
	case 15:
		return cWhite;

	default:
		return cTransparent;
	}
}

// Constructs a new color with cLightGray foreground and cBlack background
Color::Color()
{
	RunCallback(evBeforeConstruct);

	foreground(cLightGray)->background(cBlack);

	RunCallback(evAfterConstruct);
}

// Constructs a new color with same foreground and background values
Color::Color(const ConsoleColor & color)
{
	RunCallback(evBeforeConstruct);

	foreground(color)->background(color);

	RunCallback(evAfterConstruct);
}


// Constructs a new color with given foreground and background values
Color::Color(const ConsoleColor & foregroundColor, const ConsoleColor & backgroundColor)
{
	RunCallback(evBeforeConstruct);

	foreground(foregroundColor)->background(backgroundColor);

	RunCallback(evAfterConstruct);
}

Color::~Color() 
{
	RunCallback(evBeforeDestruct);
	RunCallback(evAfterDestruct);
};

// Set foreground and background values of an existing Color
Color * Color::Set(const ConsoleColor & foregroundColor, const ConsoleColor & backgroundColor)
{
	foreground(foregroundColor)->background(backgroundColor);
	return this;
}

// UD: Converts this color to grayscaled version
Color * Color::Grayscale()
{
	foreground(GetGrayscaleColor(_foreground))->background(GetGrayscaleColor(_background));
	return this;
}

// UD: Returns this color in grayscaled version
Color Color::Grayscaled(const Color & color) const
{
	return *Color(color).Grayscale();
}

// Set foreground color
Color * Color::foreground(const ConsoleColor & foregroundColor)
{
	if (_foreground != foregroundColor)
	{
		_foreground = foregroundColor;
		ScheduleRun(evChangeForeground);
		ScheduleRun(evChange);
	}

	return this;
}

// Set background color
Color * Color::background(const ConsoleColor & backgroundColor)
{
	if (_background != backgroundColor)
	{
		_background = backgroundColor;
		ScheduleRun(evChangeBackground);
		ScheduleRun(evChange);
	}

	return this;
}

// Returns a color in a string form
string Color::ToString(bool simple) const
{
	if (simple)
	{
		return _ToStringSimple(MAKE_OBJ_PARAM(_foreground), MAKE_OBJ_PARAM(_background));
	}
	else
	{
		return VAR_TYPE(this) + string(":\n") + _ToString(MAKE_OBJ_PARAM(_foreground), MAKE_OBJ_PARAM(_background));
	}
}

Color & Color::operator=(const Color & c)
{
	foreground(c._foreground)->background(c._background);
	return *this;
}
