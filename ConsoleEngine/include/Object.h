////////////////////////////////////////////////////////////////
//                                                            //
//      Object.h                                              //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_OBJECT_H
#define CONSOLE_ENGINE_OBJECT_H

#include <map>
#include <vector>
#include "Defines.h"
#include "Stringifiable.h"
#include "EventController.h"

namespace ConsoleEngine
{
    // Parent class for all interactive scene objects
	class CONSOLE_ENGINE_API Object : private _Stringifiable,
                                      public _EventController<Object>
	{
	public:
		Object() {};
        Object(std::vector<Object *> * objectsStack)
		{
			RunCallback(evBeforeConstruct);

			// TODO: Actually make an ObjectsStack class with methods Add and Remove to handle this
			_objectsStack = objectsStack;
			_objectsStack->push_back(this);
			objectsStackIndex = _objectsStack->size() - 1;

			RunCallback(evAfterConstruct);
		}

        ~Object()
		{
			RunCallback(evBeforeDestruct);

			_objectsStack->erase(_objectsStack->begin() + objectsStackIndex);

			RunCallback(evAfterDestruct);
		};

    private:
		std::vector<Object *> * _objectsStack;

		unsigned objectsStackIndex = -1;
        //std::map<std::string, Component> _components;
    };
}

#endif
