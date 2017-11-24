////////////////////////////////////////////////////////////////
//                                                            //
//      Vec2.h                                                //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_VEC2_H
#define CONSOLE_ENGINE_VEC2_H

#include "Stringifiable.h"
#include "EventController.h"
#include "YMath.h"

namespace ConsoleEngine
{
    // Representation of 2D vectors and points
    class CONSOLE_ENGINE_API Vec2 : private _Stringifiable,
                                    public _EventController<Vec2>
    {
    public:
        // UD: Shorthand for writing Vec2(0, 0)
        static const Vec2 zero;

        // UD: Shorthand for writing Vec2(-1, -1)
        static const Vec2 one;

        // UD: Shorthand for writing Vec2(0, -1)
        static const Vec2 up;

        // UD: Shorthand for writing Vec2(0.0, -1.0)
        static const Vec2 down;

        // UD: Shorthand for writing Vec2(-1.0, 0.0)
        static const Vec2 left;

        // UD: Shorthand for writing Vec2(1.0, 0.0)
        static const Vec2 right;

        // UD: Linearly interpolates between vectors a and b by t
        //   The parameter t is clamped to the range[0, 1]
        //   When t = 0 returns v1
        //   When t = 1 return v2
        //   When t = 0.5 returns the midpoint of v1 and v2
        static Vec2 Lerp(const Vec2 & v1, const Vec2 & v2, double t);

        // UD: Linearly interpolates between vectors a and b by t
        //   When t = 0 returns v1
        //   When t = 1 return v2
        //   When t = 0.5 returns the midpoint of v1 and v2
        static Vec2 LerpUnclamped(const Vec2 & v1, const Vec2 & v2, const double & t);

        // UD: Moves a point current towards target
        //   This is essentially the same as Vec2::Lerp but instead
        //   the function will ensure that the speed never exceeds
        //   maxDistanceDelta. Negative values of maxDistanceDelta
        //   pushes the vector away from target
        static Vec2 MoveTowards(const Vec2 & current, const Vec2 & target, const double & maxDistanceDelta);

		// UD: Reflects a vector off the vector defined by a normal
		static Vec2 Reflect(const Vec2 & inDirection, const Vec2 & inNormal);

        // UD: Returns a vector that is made from the smallest components of two vectors
        static Vec2 Min(const Vec2 & v1, const Vec2 & v2);

        // UD: Returns a vector that is made from the largest components of two vectors
        static Vec2 Max(const Vec2 & v1, const Vec2 & v2);

        // UD: Gradually changes a vector towards a desired goal over time
        //   The vector is smoothed by some spring - damper like function,
        //   which will never overshoot.
        static Vec2 SmoothDamp(const Vec2 & current, const Vec2 & target, Vec2 * currentVelocity, double smoothTime, const double & maxSpeed, const double & deltaTime);

		// Constructs a new vector with 0,0 values
        Vec2();

        // UD: Constructs a new vector with given X and Y values
        Vec2(const double & posX, const double & posY);

        ~Vec2();

        // UD: Set X and Y values of an existing Vec2
        Vec2 * Set(const double & posX, const double & posY);

        // UD: Multiplies existing vector variable-wise
        Vec2 * Scale(const Vec2 & v);

        // UD: Returns the length of this vector
        double Magnitude() const;

        // UD: Returns the squared length of this vector
        //   Calculating the squared magnitude instead of the magnitude
        //   is much faster. Often if you are comparing magnitudes of two vectors
        //   you can just compare their squared magnitudes.
        double SqrMagnitude() const;

		// UD: Dot Product of this vector and another one
		//   For normalized vectors Dot returns 1 if they point in exactly
		//   the same direction; -1 if they point in completely opposite
		//   directions; and a number in between for other cases
		//   (e.g. Dot returns zero if vectors are perpendicular). For
		//   vectors of arbitrary length the Dot return values are similar :
		//   they get larger when the angle between vectors decreases
		double Dot(const Vec2 & v) const;

		// Returns the unsigned angle assuming that this and v are points
		double AngleToPoint(const Vec2 & v) const;

		// UD: Returns the unsigned angle in degrees between this and v
		//   The angle returned is the unsigned acute angle between the
		//   two vectors.This means the smaller of the two possible angles
		//   between the two vectors is used.The result is never greater
		//   than 180 degrees.
		double Angle(const Vec2 & v) const;

		// UD: Returns the signed angle in degrees between this and v
		//   The angle returned is the signed acute clockwise angle between
		//   the two vectors.This means the smaller of the two possible
		//   angles between the two vectors is used.The result is never
		//   greater than 180 degrees or smaller than - 180 degrees
		double SignedAngle(const Vec2 & v) const;

		// UD: Returns the distance between this and v
		double Distance(Vec2 & v) const;

		// UD: Returns new vector with a magnitude of 1
		//   When normalized, a vector keeps the same direction but its length
		//   is 1.0. Note that the current vector is unchanged and a new normalized
		//   vector is returned.If you want to normalize the current vector, use
		//   .Normalize() function. If the vector is too small to be normalized a
		//   zero vector will be returned.
		Vec2 Normalized() const;

		// UD: Clamps magnitude of this vector to maxLength
		Vec2 * ClampMagnitude(const double & maxLength);

        // UD: Makes this vector have a magnitude of 1
        //   When normalized, a vector keeps the same direction but its length
        //   is 1.0. Note that this function will change the current  vector. If
        //   you want to keep the current vector unchanged, use .Normalized().
        //   If this vector is too small to be normalized it will be set to zero.
        Vec2 * Normalize();

		// Alternative to x(). Returns width
		double width() const
        {
            return _x;
        }

		// Alternative to x(). Sets width
		Vec2 * width(const double & width)
        {
            return x(width);
        };

		// Alternative to y(). Returns height
		double height() const
        {
            return _y;
        }

		// Alternative to y(). Sets height
		Vec2 * height(const double & height)
        {
            return y(height);
        }

        // Get X point
        double x() const
        {
            return _x;
        }

        // Set X point
		Vec2 * x(const double & posX);

        // Get Y point
        inline double y() const
        {
            return _y;
        }

        // Set Y point
		Vec2 * y(const double & posY);

        // Returns a coordinates pair in a string form
        //   simple: bool, if true - returns only values, defaults to false
        std::string ToString(bool simple = false) const;

        Vec2 & operator=(const Vec2 &);
        Vec2 & operator+=(const Vec2 &);
        Vec2 & operator-=(const Vec2 &);
        Vec2 & operator*=(const Vec2 &);
        Vec2 & operator/=(const Vec2 &);
        Vec2 & operator+=(const double &);
        Vec2 & operator-=(const double &);
        Vec2 & operator*=(const double &);
        Vec2 & operator/=(const double &);
        Vec2 operator+(const Vec2 &) const;
        Vec2 operator-(const Vec2 &) const;
        Vec2 operator*(const Vec2 &) const;
        Vec2 operator/(const Vec2 &) const;
        Vec2 operator-() const;
        Vec2 operator+(const double &) const;
        Vec2 operator-(const double &) const;
        Vec2 operator*(const double &) const;
        Vec2 operator/(const double &) const;
        friend Vec2 operator+(const double & d, const Vec2 & v)
        {
            return v + d;
        }
        friend Vec2 operator*(const double & d, const Vec2 & v)
        {
            return v * d;
        }
        friend std::ostream & operator<<(std::ostream & os, const Vec2 & v)
        {
			os << v.ToString(true); return os;
		}
        friend bool operator==(const Vec2 & v1, const Vec2 & v2)
        {
			return YMath::IsEqualDouble(v1._x, v2._x) && YMath::IsEqualDouble(v1._y, v2._y);
		}
        friend bool operator!=(const Vec2 & v1, const Vec2 & v2)
        {
            return !operator==(v1, v2);
        }

    private:
        // X point
        double _x;

        // Y point
        double _y;
    };

	typedef Vec2 Size2;
}

#endif
