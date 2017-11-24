////////////////////////////////////////////////////////////////
//                                                            //
//      Utils.h                                               //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_UTILS_H
#define CONSOLE_ENGINE_UTILS_H

// TODO: fix colors
#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include "Defines.h"
//#include "Color.h"

namespace ConsoleEngine
{
    // Class which holds common static util functions
    // WARNING: Not recommended to use outside of ConsoleEngine internals
    class CONSOLE_ENGINE_API _Utils
    {
    public:
        // Returns string type of any value
        template <typename T>
        static std::string AnyToString(T x)
        {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(5) << x << std::scientific;
            return ss.str();
        }

        // Sets the color of the output
        //static void SetColor(const ConsoleEngine::Color & c);

        // Crashes the program instantly
        static void Crash(const std::string & reason);

    private:
        _Utils();
        ~_Utils();
    };
}

#endif
