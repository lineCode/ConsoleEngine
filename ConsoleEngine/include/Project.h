////////////////////////////////////////////////////////////////
//                                                            //
//      Project.h                                             //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_PROJECT_H
#define CONSOLE_ENGINE_PROJECT_H

#include "Defines.h"
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
		Project()
        {
            RunCallback(evBeforeConstruct);

            _display = ConsoleEngine::Display();

            RunCallback(evAfterConstruct);
        }

        ~Project()
		{
			RunCallback(evBeforeDestruct);
			RunCallback(evAfterDestruct);
		}

        ConsoleEngine::Display * Display() { return &_display; }

    private:
        ConsoleEngine::Display _display;
    };
}

#endif
