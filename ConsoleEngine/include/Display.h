////////////////////////////////////////////////////////////////
//                                                            //
//      Display.h                                             //
//      HaselLoyance 2017, Unlicense                          //
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

		void size(const Size2 & s, bool showScrollbar = true);
		void color(const Color & color);

		bool IsScrollbarVisible() const
		{
			return &_scrollbarVisible;
		}

		const Size2 * size() const
		{
			return &_size;
		}

		const Color * color() const
		{
			return &_color;
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
