////////////////////////////////////////////////////////////////
//                                                            //
//      EventController.h                                     //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_EVENTCONTROLLER_H
#define CONSOLE_ENGINE_EVENTCONTROLLER_H

#include <vector>
#include <map>
#include <algorithm>
#include <functional>
#include "Defines.h"

namespace ConsoleEngine
{
	// All possible events that objects emit so far
	// evCustomN is for user defined events in user-extended objects
	enum Event
	{
		evBeforeConstruct,
		evAfterConstruct,
		evBeforeDestruct,
		evAfterDestruct,
		evChange,
		evChangeVec2,
		evChangeX,
		evChangeY,
		evChangeColor,
		evChangeForeground,
		evChangeBackground,
		evChangeSize,
		evChangeScrollbar,

		evCustom0,
		evCustom1,
		evCustom2,
		evCustom3,
		evCustom4,
		evCustom5,
		evCustom6,
		evCustom7,
		evCustom8,
		evCustom9,
	};

	// Adds class to track any changes and runs bounded callbacks
	template<class DerivedType>
	class _EventController
	{
	public:
		// Binds a callback function to event's name for class
		//   ev, Event, event value
		//   callback, pointer to void callback function which accepts
		//     object pointer as a parameter
		// eg: Color::OnOnGlobal(evChange, [](Color * c){ cout << c << endl; });
		static void OnGlobal(const Event & ev, const std::function<void(DerivedType*)> & callback)
		{
			_eventsGlobal[ev] = callback;
		}

		// Unbinds a callback function from event's name for class
		//   ev, Event, event value
		// eg: Color::OffGlobal(evChange);
		static void OffGlobal(const Event & ev)
		{
			_eventsGlobal.erase(ev);
		}

		// Schedules an event to run at the end of the ActionLoop cycle for class
		//   ev, Event, event value
		static void ScheduleRunGlobal(const Event & ev)
		{
			if (std::find(_scheduledEventsGlobal.begin(), _scheduledEventsGlobal.end(), ev)
				== _scheduledEventsGlobal.end())
			{
				_scheduledEventsGlobal.push_back(ev);
			}
		}

		// Binds a callback function to event's name for an object
		//   ev, Event, event value
		//   callback, pointer to void callback function which accepts
		//     object pointer as a parameter
		// eg: color.On("Change", [](Color * c){ cout << c << endl; });
		DerivedType * On(const Event & ev, const std::function<void(DerivedType*)> & callback)
		{
			_events[ev] = callback;
			return static_cast<DerivedType*>(this);
		}

		// Unbinds a callback function from event's name for an object
		//   ev, Event, event value
		// eg: color.Off("Change");
		DerivedType * Off(const Event & ev)
		{
			_events.erase(ev);
			return static_cast<DerivedType*>(this);
		}

		// Runs on every ActionLoop cycle end before running OnCycleEnd()
		// Allows to run all other callbacks in an object. See Display class for usage
		// TODO: probably move to ActionLoopElement so it works directly with ActionLoop
		virtual DerivedType * _CycleEnd()
		{
			_OnCycleEnd();
			return static_cast<DerivedType*>(this);
		}

	protected:
		_EventController() {}
		~_EventController() {}

		// Schedules an event to run at the end of the ActionLoop cycle for an object
		//   ev, Event, event value
		DerivedType * ScheduleRun(const Event & ev)
		{
			if (std::find(_scheduledEvents.begin(), _scheduledEvents.end(), ev) == _scheduledEvents.end())
			{
				_scheduledEvents.push_back(ev);
			}

			return static_cast<DerivedType*>(this);
		}

		// Runs a callback
		//   ev, Event, event value
		// returns: bool, true if callback ran, false otherwise
		bool RunCallback(const Event & ev)
		{
			bool isGood = false;

			// Run object-bound events
			if (_eventsGlobal.size() > 0 && _eventsGlobal.find(ev) != _eventsGlobal.end())
			{
				_eventsGlobal.at(ev)(static_cast<DerivedType*>(this));
				isGood = true;
			}

			// Run instance-bound events
			if (_events.size() && _events.find(ev) != _events.end())
			{
				_events.at(ev)(static_cast<DerivedType*>(this));
				isGood = true;
			}

			return isGood;
		}

		// Runs when every ActionLoop cycle ends
		DerivedType * _OnCycleEnd()
		{
			// Run object-bound events
			size_t size = _scheduledEventsGlobal.size();
			for (size_t i = 0; i < size; i++)
			{
				RunCallback(_scheduledEventsGlobal.front());
				_scheduledEventsGlobal.erase(_scheduledEventsGlobal.begin());
			}

			// Run instance-bound events
			size = _scheduledEvents.size();
			for (size_t i = 0; i < size; i++)
			{
				RunCallback(_scheduledEvents.front());
				_scheduledEvents.erase(_scheduledEvents.begin());
			}

			return static_cast<DerivedType*>(this);
		}

	private:
		// Stores name of events to run at the end of ActionLoop cycle, for binding to specific objects
		std::vector<Event> _scheduledEvents;

		// Map to store callbacks and access them by event names, for binding to specific objects
		std::map<Event, std::function<void(DerivedType*)>> _events;

		// Stores name of events to run at the end of ActionLoop cycle, for binding to entire objects
		static std::vector<Event> _scheduledEventsGlobal;

		// Map to store callbacks and access them by event names, for binding to entire objects
		static std::map<Event, std::function<void(DerivedType*)>> _eventsGlobal;
	};

	template<class DerivedType>
	std::map<Event, std::function<void(DerivedType*)>> _EventController<DerivedType>::_eventsGlobal;

	template<class DerivedType>
	std::vector<Event> _EventController<DerivedType>::_scheduledEventsGlobal;
}
#endif
