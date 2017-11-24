////////////////////////////////////////////////////////////////
//                                                            //
//      DisplayTemp.cpp                                       //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

// WARNING: this is a placeholder for interactions with console screen
// Display class will do the work in the future and this will be removed

#include "../include/DisplayTemp.h"

using namespace std;
using namespace ConsoleEngine;

DisplayTemp::DisplayTemp()
{
	RunCallback(evBeforeConstruct);

	// TODO: Default constructor data initialization
#ifdef _WIN32
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(h, &_cBuffer);
#endif

	RunCallback(evAfterConstruct);
}

DisplayTemp::~DisplayTemp()
{
	RunCallback(evBeforeDestruct);
	RunCallback(evAfterDestruct);
}

void DisplayTemp::Size(const Size2 & s, bool showScrollbar)
{
	int16_t width = round(s.width());
	int16_t height = round(s.height());

#ifdef _WIN32
	SMALL_RECT & winInfo = _cBuffer.srWindow;
	COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

	if (windowSize.X > width || windowSize.Y > height)
	{
		SMALL_RECT info = { 0, 0, width < windowSize.X ? width - 1 : windowSize.X - 1,
			height < windowSize.Y ? height - 1 : windowSize.Y - 1 };
		SetConsoleWindowInfo(h, TRUE, &info);
	}


	SetConsoleScreenBufferSize(h, { width, showScrollbar ? 9999 : height });
	SMALL_RECT info = { 0, 0, width - 1, height - 1 };
	SetConsoleWindowInfo(h, TRUE, &info);
#else
	cout << VK_ESCAPE_CHAR << "[8;" << height << ";" << width << "t";
#endif

	if (showScrollbar != _scrollbarVisible)
	{
		ScheduleRun(evChangeScrollbar);
	}

	_size = s;
	_scrollbarVisible = showScrollbar;

	ScheduleRun(evChangeSize);
	ScheduleRun(evChange);
}

void DisplayTemp::Color(const ConsoleEngine::Color & c)
{
#ifdef _WIN32
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((c.background() << 4) | c.foreground()));

#else

	cout << VK_ESCAPE_CHAR;
	switch (c.foreground())
	{
	case cBlack: cout << "[30m"; break;
	case cBlue: cout << "[34m"; break;
	case cGreen: cout << "[32m"; break;
	case cCyan: cout << "[36m"; break;
	case cRed: cout << "[31m"; break;
	case cMagenta: cout << "[35m"; break;
	case cBrown: cout << "[33m"; break;
	case cLightGray: cout << "[37m"; break;
	case cGray: cout << "[90m"; break;
	case cLightBlue: cout << "[94m"; break;
	case cLightGreen: cout << "[92m"; break;
	case cLightCyan: cout << "[96m"; break;
	case cLightRed: cout << "[91m"; break;
	case cLightMagenta: cout << "[95m"; break;
	case cYellow: cout << "[93m"; break;
	case cWhite: cout << "[97m"; break;
	}

	cout << VK_ESCAPE_CHAR;
	switch (c.background())
	{
	case cBlack: cout << "[40m"; break;
	case cBlue: cout << "[44m"; break;
	case cGreen: cout << "[42m"; break;
	case cCyan: cout << "[46m"; break;
	case cRed: cout << "[41m"; break;
	case cMagenta: cout << "[45m"; break;
	case cBrown: cout << "[43m"; break;
	case cLightGray: cout << "[47m"; break;
	case cGray: cout << "[100m"; break;
	case cLightBlue: cout << "[104m"; break;
	case cLightGreen: cout << "[102m"; break;
	case cLightCyan: cout << "[106m"; break;
	case cLightRed: cout << "[101m"; break;
	case cLightMagenta: cout << "[105m"; break;
	case cYellow: cout << "[103m"; break;
	case cWhite: cout << "[107m"; break;
	}
#endif

	_color = c;
	ScheduleRun(evChangeColor);
	ScheduleRun(evChange);
}

DisplayTemp * DisplayTemp::_CycleEnd()
{
	_size._CycleEnd();
	_color._CycleEnd();
	_OnCycleEnd();

	return this;
}
