/* BasicTypes.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

This header file controls basic types used as the part of YOLConsoleEngine:
__Size2 : stores width and height and operates with them
__Vec2 : stores x and y points and operates with them 
__EngineErrors : all possible YOLConsoleEngine errors

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_BASICTYPES_H
#define YOL_CONSOLE_ENGINE_BASICTYPES_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	class YOL_ENGINE_API __Vec2
	{
	public:
		//Creates a vector of two 0 points
		__Vec2();

		//Creates a vector of two specified points
		__Vec2(const double & posX, const double & posY);

		~__Vec2();


		//Point x value
		double x;

		//Point y value
		double y;
	};
	
	class YOL_ENGINE_API __Size2
	{
		friend class __Sprite;
		friend class __Project;
		friend class FontSet;
	public:
		//Creates a pair of two 0 dimensions
		__Size2();

		//Creates a pair of two specified dimensions
		__Size2(const unsigned int & width, const unsigned int & h);

		~__Size2();


		//Returns width value
		inline unsigned int Width() { return width; }

		//Returns height value
		inline unsigned int Height() { return height; }

	private:
		unsigned int width;
		unsigned int height;
	};


	//Stores all possible engine errors
	enum __EngineErrors
	{
		EMPTY_ERROR,
		SUCCESS,
		WRONG_INPUT_TYPE,
		FILE_COPY_FAIL,
		FILE_DECRYPT_FAIL,
		FILE_NOT_FOUND,
		FILE_STREAM_ERROR,
		FILE_EMPTY,
	};

	//Processes error code and returns error message in text
	YOL_ENGINE_API std::wstring ProcessEngineError(const __EngineErrors & error);
}
#endif
