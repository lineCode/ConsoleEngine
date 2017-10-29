////////////////////////////////////////////////////////////////
//                                                            //
//      DisplayTemp.h                                         //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

// WARNING: this is a placeholder for interactions with console screen
// Display class will do the work in the future and this will be removed

#ifndef CONSOLE_ENGINE_DISPLAY_TEMP_H
#define CONSOLE_ENGINE_DISPLAY_TEMP_H

#include "Stringifiable.h"
#include "EventController.h"
#include "Vec2.h"
#include "Color.h"

namespace ConsoleEngine
{
	// Representation of display object for size and output text color
	class CONSOLE_ENGINE_API DisplayTemp : _Stringifiable, public _EventController<DisplayTemp>
	{
	public:
		DisplayTemp();
		~DisplayTemp();

		void Size(const Size2 & s, bool showScrollbar = true);
		void Color(const Color & color);

		inline bool IsScrollbarVisible() const { return _scrollbarVisible; }
		inline ConsoleEngine::Size2 Size() const { return _size; }
		inline ConsoleEngine::Color Color() const { return _color; }

		DisplayTemp * _CycleEnd();

	private:
#ifdef _WIN32
		CONSOLE_SCREEN_BUFFER_INFO _cBuffer;
		// TODO: cache handler in gamecontroller or something
		HANDLE h;
#endif
		bool _scrollbarVisible;
		ConsoleEngine::Color _color;
		Size2 _size;
	};
}

#endif
