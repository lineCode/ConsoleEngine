////////////////////////////////////////////////////////////////
//                                                            //
//      Display.h                                             //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_DISPLAY_H
#define CONSOLE_ENGINE_DISPLAY_H

#include "Stringifiable.h"
#include "EventController.h"
#include "Singleton.h"
#include "Vec2.h"
#include "Color.h"

namespace ConsoleEngine
{
	// Representation of display object for size and output text color
	class CONSOLE_ENGINE_API Display : private _Stringifiable,
									   public _EventController<Display>,
									   public _Singleton<Display>
	{
	public:
		Display();
		~Display();

		void Size(const Size2 & s, bool showScrollbar = true);
		void Color(const Color & color);

		bool IsScrollbarVisible() const
		{
			return _scrollbarVisible;
		}

		ConsoleEngine::Size2 Size() const
		{
			return _size;
		}

		ConsoleEngine::Color Color() const
		{
			return _color;
		}

		Display * _CycleEnd();

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
