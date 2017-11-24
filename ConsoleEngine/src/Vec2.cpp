////////////////////////////////////////////////////////////////
//                                                            //
//      Vec2.cpp                                              //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#include "../include/Vec2.h"

using namespace std;
using namespace ConsoleEngine;

// UD: Shorthand for writing Vec2(0.0, 0.0)
const Vec2 Vec2::zero = Vec2(0.0, 0.0);

// UD: Shorthand for writing Vec2(1.0, 1.0)
const Vec2 Vec2::one = Vec2(1.0, 1.0);

// UD: Shorthand for writing Vec2(0.0, -1.0)
const Vec2 Vec2::up = Vec2(0.0, -1.0);

// UD: Shorthand for writing Vec2(0.0, 1.0)
const Vec2 Vec2::down = Vec2(0.0, 1.0);

// UD: Shorthand for writing Vec2(-1.0, 0.0)
const Vec2 Vec2::left = Vec2(-1.0, 0.0);

// UD: Shorthand for writing Vec2(1.0, 0.0)
const Vec2 Vec2::right = Vec2(1.0, 0.0);

// UD: Linearly interpolates between vectors a and b by t
//   The parameter t is clamped to the range[0, 1]
Vec2 Vec2::Lerp(const Vec2 & v1, const Vec2 & v2, double t)
{
    t = YMath::Clamp01(t);
    return Vec2(v1._x + (v2._x - v1._x) * t, v1._y + (v2._y - v1._y) * t);
}

// UD: Linearly interpolates between vectors a and b by t
Vec2 Vec2::LerpUnclamped(const Vec2 & v1, const Vec2 & v2, const double & t)
{
    return Vec2(v1._x + (v2._x - v1._x) * t, v1._y + (v2._y - v1._y) * t);
}

// UD: Moves a point current towards target
Vec2 Vec2::MoveTowards(const Vec2 & current, const Vec2 & target, const double & maxDistanceDelta)
{
    Vec2 a = target - current;
    double magnitude = a.Magnitude();
    return (magnitude <= maxDistanceDelta || YMath::IsEqualDouble(magnitude, 0.0)) ? target : current + a / magnitude * maxDistanceDelta;
}

// UD: Reflects a vector off the vector defined by a normal
Vec2 Vec2::Reflect(const Vec2 & inDirection, const Vec2 & inNormal)
{
	return inNormal *inNormal.Dot(inDirection) * -2.0 + inDirection;
}

// UD: Returns a vector that is made from the smallest components of two vectors
Vec2 Vec2::Min(const Vec2 & v1, const Vec2 & v2)
{
    return Vec2(min(v1._x, v2._x), min(v1._y, v2._y));
}

// UD: Returns a vector that is made from the largest components of two vectors
Vec2 Vec2::Max(const Vec2 & v1, const Vec2 & v2)
{
    return Vec2(max(v1._x, v2._x), max(v1._y, v2._y));
}

// UD: Gradually changes a vector towards a desired goal over time
Vec2 Vec2::SmoothDamp(const Vec2 & current, const Vec2 & target, Vec2 * currentVelocity, double smoothTime, const double & maxSpeed, const double & deltaTime)
{
    smoothTime = max(0.0001, smoothTime);
    double num = 2.0 / smoothTime;
    double num2 = num * deltaTime;
    double d = 1.0 / (1.0 + num2 + 0.48 * num2 * num2 + 0.235 * num2 * num2 * num2);
    Vec2 v1 = current - target;
    Vec2 v2 = target;
    double maxLength = maxSpeed * smoothTime;
    v1.ClampMagnitude(maxLength);
    Vec2 v3 = (v1 * num + *currentVelocity) * deltaTime;
    *currentVelocity = (*currentVelocity - v3 * num) * d;
    Vec2 v4 = current - v1 + (v1 + v3) * d;
    if ((v2 - current).Dot(v4 - v2) > 0.0)
    {
        v4 = v2;
        *currentVelocity = (v4 - v2) / deltaTime;
    }
    return v4;
}


// UD: Constructs a new vector with 0,0 values
Vec2::Vec2()
{
	RunCallback(evBeforeConstruct);

	x(0)->y(0);

	RunCallback(evAfterConstruct);
}

// UD: Constructs a new vector with given X and Y values
Vec2::Vec2(const double & posX, const double & posY)
{
	RunCallback(evBeforeConstruct);

	x(posX)->y(posY);

	RunCallback(evAfterConstruct);
}

Vec2::~Vec2()
{
	RunCallback(evBeforeDestruct);
	RunCallback(evAfterDestruct);
}

// UD: Set X and Y values of an existing Vec2
Vec2 * Vec2::Set(const double & posX, const double & posY)
{
	x(posX)->y(posY);
	return this;
}

// UD: Multiplies existing vector variable-wise
Vec2 * Vec2::Scale(const Vec2 & v)
{
    *this *= v;
	return this;
}

// UD: Returns the length of this vector
double Vec2::Magnitude() const
{
    return sqrt(_x * _x + _y * _y);
}

// UD: Returns the squared length of this vector
double Vec2::SqrMagnitude() const
{
    return _x * _x + _y * _y;
}

// UD: Dot Product of this vector and v
double Vec2::Dot(const Vec2 & v) const
{
	return _x * v._x + _y * v._y;
}

// Returns the unsigned angle assuming that this and v are points
double Vec2::AngleToPoint(const Vec2 & v) const
{
	Vec2 normalized = (v - *this).Normalized();
	return atan2(normalized._y, normalized._x) * RAD2DEG;
}

// UD: Returns the unsigned angle in degrees between this and v
double Vec2::Angle(const Vec2 & v) const
{
	return acos(YMath::Clamp(this->Normalized().Dot(v.Normalized()), -1.0, 1.0)) * RAD2DEG;
}

// UD: Returns the signed angle in degrees between this and v
double Vec2::SignedAngle(const Vec2 & v) const
{
	Vec2 normalized1 = this->Normalized();
	Vec2 normalized2 = v.Normalized();
	return acos(YMath::Clamp(normalized1.Dot(normalized2), -1.0, 1.0)) * RAD2DEG * YMath::Sign(normalized1._x * normalized2._y - normalized1._y * normalized2._x);
}

// UD: Returns the distance between this and v
double Vec2::Distance(Vec2 & v) const
{
	return (*this - v).Magnitude();
}

// UD: Returns new vector with a magnitude of 1
Vec2 Vec2::Normalized() const
{
	return *Vec2(*this).Normalize();
}

// UD: Clamps magnitude of this vector to maxLength
Vec2 * Vec2::ClampMagnitude(const double & maxLength)
{
	*this = SqrMagnitude() > maxLength * maxLength ? Normalized() * maxLength : *this;
	return this;
}

// UD: Makes this vector have a magnitude of 1
Vec2 * Vec2::Normalize()
{
    double magnitude = Magnitude();

	*this = YMath::IsEqualDouble(magnitude, 0) ? Vec2::zero : *this / (magnitude);

	return this;
}

// Set X point
Vec2 * Vec2::x(const double & posX)
{
	if (!YMath::IsEqualDouble(posX, _x))
	{
		_x = posX;
		ScheduleRun(evChangeX);
		ScheduleRun(evChange);
	}

	return this;
}

// Set Y point
Vec2 * Vec2::y(const double & posY)
{
	if (!YMath::IsEqualDouble(posY, _y))
	{
		_y = posY;
		ScheduleRun(evChangeY);
		ScheduleRun(evChange);
	}

	return this;
}

// Returns a coordinates pair in string form
string Vec2::ToString(bool simple) const 
{
    if (simple)
    {
        return _ToStringSimple(MAKE_OBJ_PARAM(_x), MAKE_OBJ_PARAM(_y));
    }
    else
    {
        return VAR_TYPE(this) + string(":\n") + _ToString(MAKE_OBJ_PARAM(_x), MAKE_OBJ_PARAM(_y));
    }
}

Vec2 & Vec2::operator=(const Vec2 & v)
{
	x(v._x)->y(v._y);
    return *this;
}

Vec2 & Vec2::operator+=(const Vec2 & v)
{
	x(_x + v._x)->y(_y + v._y);
    return *this;
}

Vec2 & Vec2::operator-=(const Vec2 & v)
{
	x(_x - v._x)->y(_y - v._y);
    return *this;
}

Vec2 & Vec2::operator*=(const Vec2 & v)
{
	x(_x * v._x)->y(_y * v._y);
    return *this;
}

Vec2 & Vec2::operator/=(const Vec2 & v)
{
	x(_x / v._x)->y(_y / v._y);
    return *this;
}

Vec2 & Vec2::operator+=(const double & d)
{
	x(_x + d)->y(_y + d);
    return *this;
}

Vec2 & Vec2::operator-=(const double & d)
{
	x(_x - d)->y(_y - d);
    return *this;
}

Vec2 & Vec2::operator*=(const double & d)
{
	x(_x * d)->y(_y * d);
    return *this;
}

Vec2 & Vec2::operator/=(const double & d)
{
	x(_x / d)->y(_y / d);
    return *this;
}

Vec2 Vec2::operator+(const Vec2 & v) const
{
    return Vec2(_x + v._x, _y + v._y);
}

Vec2 Vec2::operator-(const Vec2 & v) const
{
    return Vec2(_x - v._x, _y - v._y);
}

Vec2 Vec2::operator-() const
{
    return Vec2(-_x, -_y);
}

Vec2 Vec2::operator*(const Vec2 & v) const
{
    return Vec2(_x * v._x, _y * v._y);
}

Vec2 Vec2::operator/(const Vec2 & v) const
{
    return Vec2(_x / v._x, _y / v._y);
}

Vec2 Vec2::operator+(const double & d) const
{
    return Vec2(_x + d, _y + d);
}

Vec2 Vec2::operator-(const double & d) const
{
    return Vec2(_x - d, _y - d);
}

Vec2 Vec2::operator*(const double & d) const
{
    return Vec2(_x * d, _y * d);
}

Vec2 Vec2::operator/(const double & d) const
{
    return Vec2(_x / d, _y / d);
}
