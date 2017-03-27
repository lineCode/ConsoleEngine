/* BasicTypes.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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



//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngineMain.h"

namespace YOLConsoleEngine
{
	//Creates a pair of two 0 points
	__Vec2::__Vec2()
	{
		x = 0;
		y = 0;
	}

	//Creates a pair of two specified points
	__Vec2::__Vec2(const double & x, const double & y)
	{
		__Vec2::x = x;
		__Vec2::y = y;
	}

	__Vec2::~__Vec2() {}


	//Creates pair of two 0 dimesions
	__Size2::__Size2()
	{
		width = 0;
		height = 0;
	}

	//Creates pair of two specified dimesions
	__Size2::__Size2(const unsigned int & width, const unsigned int & height)
	{
		__Size2::width = width;
		__Size2::height = height;
	}

	__Size2::~__Size2() {}


	//Processes error code and returns error message in text
	std::wstring ProcessEngineError(const __EngineErrors & error)
	{
		switch (error)
		{
		case FILE_COPY_FAIL:		return L"FILE_COPY_FAIL";
		case FILE_DECRYPT_FAIL:		return L"FILE_DECRYPT_FAIL";
		case FILE_EMPTY:			return L"FILE_EMPTY";
		case SUCCESS:				return L"SUCCESS";
		case FILE_STREAM_ERROR:		return L"FILE_STREAM_ERROR";
		}
	}
}