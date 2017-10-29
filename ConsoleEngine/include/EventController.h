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
	// Adds class to track any changes and runs binded callbacks
	template<class DerivedType>
	class _EventController
	{
	public:
		// Binds a callback function to event's name for class
		//   eventName, string, name of the event
		//   callback, pointer to void callback function which accepts
		//     object pointer as a parameter
		// eg: Color::OnOnGlobal("Change", [](Color * c){ cout << c << endl; });
		static void OnGlobal(const std::string & eventName, const std::function<void(DerivedType*)> & callback)
		{
			_eventsGlobal[eventName] = callback;
		}

		// Unbinds a callback function from event's name for class
		//   eventName, string, name of the event
		// eg: Color::OffGlobal("Change");
		static void OffGlobal(const std::string & eventName)
		{
			_eventsGlobal.erase(eventName);
		}

		// Schedules an event to run at the end of the ActionLoop cycle for class
		//   eventName, string, name of the event
		static void ScheduleRunGlobal(const std::string & eventName)
		{
			if (std::find(_scheduledEventsGlobal.begin(), _scheduledEventsGlobal.end(), eventName)
				== _scheduledEventsGlobal.end())
			{
				_scheduledEventsGlobal.push_back(eventName);
			}
		}

		// Binds a callback function to event's name for an object
		//   eventName, string, name of the event
		//   callback, pointer to void callback function which accepts 
		//     object pointer as a parameter
		// eg: color.On("Change", [](Color * c){ cout << c << endl; });
		DerivedType * On(const std::string & eventName, const std::function<void(DerivedType*)> & callback)
		{
			_events[eventName] = callback;
			return static_cast<DerivedType*>(this);
		}

		// Unbinds a callback function from event's name for an object
		//   eventName, string, name of the event
		// eg: color.Off("Change");
		DerivedType * Off(const std::string & eventName)
		{
			_events.erase(eventName);
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
		//   eventName, string, name of the event
		DerivedType * ScheduleRun(const std::string & eventName)
		{
			if (std::find(_scheduledEvents.begin(), _scheduledEvents.end(), eventName) == _scheduledEvents.end())
			{
				_scheduledEvents.push_back(eventName);
			}

			return static_cast<DerivedType*>(this);
		}

		// Runs a callback
		//   eventName, string, name of the event
		// returns: bool, true if callback ran, false otherwise
		bool RunCallback(const std::string & eventName)
		{
			bool isGood = false;

			// Run class-binded events
			if (_eventsGlobal.size() > 0 && _eventsGlobal.find(eventName) != _eventsGlobal.end())
			{
				_eventsGlobal.at(eventName)(static_cast<DerivedType*>(this));
				isGood = true;
			}

			// Run object-binded events
			if (_events.size() && _events.find(eventName) != _events.end())
			{
				_events.at(eventName)(static_cast<DerivedType*>(this));
				isGood = true;
			}

			return isGood;
		}

		// Runs when every ActionLoop cycle ends
		DerivedType * _OnCycleEnd()
		{
			// Run object-binded events
			size_t size = _scheduledEventsGlobal.size();
			for (size_t i = 0; i < size; i++)
			{
				RunCallback(_scheduledEventsGlobal.front());
				_scheduledEventsGlobal.erase(_scheduledEventsGlobal.begin());
			}

			// Run object-binded events
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
		std::vector<std::string> _scheduledEvents;

		// Map to store callbacks and access them by event names, for binding to specific objects
		std::map<std::string, std::function<void(DerivedType*)>> _events;

		// Stores name of events to run at the end of ActionLoop cycle, for binding to entire objects
		static std::vector<std::string> _scheduledEventsGlobal;

		// Map to store callbacks and access them by event names, for binding to entire objects
		static std::map<std::string, std::function<void(DerivedType*)>> _eventsGlobal;
	};

	template<class DerivedType>
	std::map<std::string, std::function<void(DerivedType*)>> _EventController<DerivedType>::_eventsGlobal;

	template<class DerivedType>
	std::vector<std::string> _EventController<DerivedType>::_scheduledEventsGlobal;
}
#endif
