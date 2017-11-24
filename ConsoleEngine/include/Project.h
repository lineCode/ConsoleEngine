////////////////////////////////////////////////////////////////
//                                                            //
//      Project.h                                             //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_PROJECT_H
#define CONSOLE_ENGINE_PROJECT_H

#include "Stringifiable.h"
#include "Singleton.h"
#include "EventController.h"
#include "Display.h"

namespace ConsoleEngine
{
	class CONSOLE_ENGINE_API Project : private _Stringifiable,
                                       public _Singleton<Project>,
                                       public _EventController<Project>
	{
	public:
		Project();
        ~Project();

        ConsoleEngine::Display * display() { return &_display; }

    private:
        ConsoleEngine::Display _display;
    };
}

#endif
