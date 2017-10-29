////////////////////////////////////////////////////////////////
//                                                            //
//      YMath.h                                               //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_MATH_H
#define CONSOLE_ENGINE_MATH_H

#include <math.h>
#include "Defines.h"

// Class with additional static math function build upon math.h
namespace ConsoleEngine
{
    class CONSOLE_ENGINE_API YMath
    {
    public:
        // Checks if two double values are equal
        static bool IsEqualDouble(const double & d1, const double & d2) { return fabs(d1 - d2) < DBL_EPSILON; }

        // UD: Clamps value between 0 and 1 and returns value
        static double Clamp01(const double & value) { return (value < 0.0 ? 0.0 : (value > 1.0 ? 1.0 : value)); }

        // UD: Clamps a value between a minimum and maximum value
        static double Clamp(const double & value, const double & min, const double & max) { return (value < min ? min : (value > max ? max : value)); }

        // UD: Returns the sign of d
        //  Return value is 1 when d is positive or zero,
        //  -1 when d is negative.
        static double Sign(const double & d) { return (d < 0.0) ? -1.0 : 1.0; }
    };
}
#endif
