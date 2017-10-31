////////////////////////////////////////////////////////////////
//                                                            //
//      Stringifiable.h                                       //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_STRINGIFIABLE_H
#define CONSOLE_ENGINE_STRINGIFIABLE_H

#include <typeinfo>
#include "Utils.h"

namespace ConsoleEngine
{
    // Parameter structure for holding JSON-like information about variable
    struct ObjParam
    {
        std::string key = "no_key";
        std::string value = "no_value";
        std::string type = "no_type";

        std::string ToString(bool putEndl = true)
        {
            return '\t' + type + ' ' + key + ": " + value + (putEndl ? '\n' : ' ');
        }
    };

    // Adds ._ToString() method on children object
    // Usage: derive a child from this class. Define a .ToString()
    //   method on child class, which returns _ToString(), where
    //   params are an unlimited number of MAKE_OBJ_PARAM(variable)
    class CONSOLE_ENGINE_API _Stringifiable
    {
    protected:
		_Stringifiable() { }
        ~_Stringifiable() { }


        // Combines all ObjParam arguments into one string
        template<typename T, typename... Args>
        std::string _ToString(T t, Args... args) const
        {
            return t.ToString() + _Convert(args...);
        }

        template<typename T, typename... Args>
        std::string _Convert(T t, Args... args) const
        {
            return t.ToString() + _Convert(args...);
        }

        template <typename T>
        std::string _Convert(T t) const
        {
            return t.ToString(false);
        }

        // Combines all ObjParam arguments into one string, but in a more minimalistic way
        template<typename T, typename... Args>
        std::string _ToStringSimple(T t, Args... args) const
        {
            return t.value + ',' + _ConvertSimple(args...);
        }

        template<typename T, typename... Args>
        std::string _ConvertSimple(T t, Args... args) const
        {
            return t.value + ',' + _ConvertSimple(args...);
        }

        template <typename T>
        std::string _ConvertSimple(T t) const
        {
            return t.value;
        }

        // Placeholder if custom .ToString() method is not defined on child object
        virtual std::string ToString(bool simple = false) const { return "Custom .ToString() method is not defined"; };
    };
}

#endif
