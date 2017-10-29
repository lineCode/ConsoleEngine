////////////////////////////////////////////////////////////////
//                                                            //
//      Colors.h                                              //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_COLORS_H
#define CONSOLE_ENGINE_COLORS_H

#include "Stringifiable.h"
#include "EventController.h"

namespace ConsoleEngine
{
	// All colors
	enum ConsoleColor
	{
		cTransparent = -1,
		cBlack = 0,
		cBlue = 1,
		cGreen = 2,
		cCyan = 3,
		cRed = 4,
		cMagenta = 5,
		cBrown = 6,
		cLightGray = 7,
		cGray = 8,
		cLightBlue = 9,
		cLightGreen = 10,
		cLightCyan = 11,
		cLightRed = 12,
		cLightMagenta = 13,
		cYellow = 14,
		cWhite = 15,
	};

	// Representation of color object for coloring and mixing
	class CONSOLE_ENGINE_API Color : private _Stringifiable, public _EventController<Color>
	{
	public:
		// UD: Shorthand for writing Color(cRed, cRed)
		static const Color red;

		// UD: Shorthand for writing Color(cGreen, cGreen)
		static const Color green;

		// UD: Shorthand for writing Color(cBlue, cBlue)
		static const Color blue;

		// UD: Shorthand for writing Color(cBlack, cBlack)
		static const Color black;

		// UD: Shorthand for writing Color(cWhite, cWhite)
		static const Color white;

		// UD: Shorthand for writing Color(cYellow, cYellow)
		static const Color yellow;

		// UD: Shorthand for writing Color(cCyan, cCyan)
		static const Color cyan;

		// UD: Shorthand for writing Color(cMagenta, cMagenta)
		static const Color magenta;

		// UD: Shorthand for writing Color(cGray, cGray)
		static const Color gray;

		// Returns grayscaled ConsoleColor
		static const ConsoleColor GetGrayscaleColor(const ConsoleColor & color);

		// Constructs a new color with cLightGray foreground and cBlack background
		Color();

		// Constructs a new color with same foreground and background values
		Color(const ConsoleColor & color);

		// Constructs a new color with given foreground and background values
		Color(const ConsoleColor & foreground, const ConsoleColor & background);

		~Color();

		// Set foreground and background values of an existing Color
		Color * Set(const ConsoleColor & foreground, const ConsoleColor & background);

		// UD: Transforms this color to grayscaled version
		Color * Grayscale();

		// UD: Returns this color in grayscaled version
		Color Grayscaled(const Color & color) const;

		// Get foreground color
		inline ConsoleColor foreground() const { return _foreground; }

		// Set foreground color
		Color * foreground(const ConsoleColor & foregroundColor);

		// Get background color
		inline ConsoleColor background() const { return _background; }

		// Set background color
		Color * background(const ConsoleColor & backgroundColor);

		// Returns a color in a string form
		//   simple: bool, if true - returns only values, defaults to false
		std::string ToString(bool simple = false) const;

		Color & operator=(const Color & c);
		friend inline std::ostream & operator<<(std::ostream & os, const Color & c) { 
			os << c.ToString(true); return os; 
		}
		friend inline bool operator==(const Color & c1, const Color & c2) { 
			return c1._foreground == c2._foreground && c1._background == c2._background;
		}
		friend inline bool operator!=(const Color & c1, const Color & c2) { return !operator==(c1, c2); }

	private:
		// Text/foreground color
		ConsoleColor _foreground;

		// Background color
		ConsoleColor _background;
	};
}
#endif
