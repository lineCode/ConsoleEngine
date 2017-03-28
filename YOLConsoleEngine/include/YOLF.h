/* YOLF.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain. 
No warranty implied; use at your own risk

This file contains all the core functions used in the YOLConsoleEngine such as:
-Console colors manipulations
-Console size manipulations
-Encryption/decryption key manipulations for secure PRNG seeds
-File/String encryption/decryption
-Some other technical functions

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


#ifndef YOL_CONSOLE_ENGINE_UTILS_YOLF_H
#define YOL_CONSOLE_ENGINE_UTILS_YOLF_H

//Global include for all YOLConsoleEngine modules
#include "YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//All colors 
	enum __ConsoleColor
	{
		cTransparent = -1,
		cBlack = 0,
		cBlue = 1,
		cGreen = 2,
		cCyan = 3,
		cRed = 4,
		cMagenta = 5,
		cBrown = 6,
		cLightGray = 7,
		cDarkGray = 8,
		cLightBlue = 9,
		cLightGreen = 10,
		cLightCyan = 11,
		cLightRed = 12,
		cLightMagenta = 13,
		cYellow = 14,
		cWhite = 15,
	};

	//Generates the seed from the key string with the little help of magic
	YOL_ENGINE_API inline unsigned long long int GetRandomSeed(std::wstring key) { return (std::hash<std::wstring>{}(key) << key.size()); }


	//Reads file contents into the vector of bytes (requires file with UTF-16 Big Endian encoding)
	YOL_ENGINE_API void ReadFileBytes(std::ifstream & inputFile, std::vector<unsigned char> & outputBytes);

	//Reads file contents and returns the vector of bytes (requires file with UTF-16 Big Endian encoding)
	YOL_ENGINE_API std::vector<unsigned char> ReadFileBytes(std::ifstream & inputFile);

	//Writes bytes into the file (requires bytes in UTF-16 Big Endian encoding)
	YOL_ENGINE_API void WriteFileBytes(std::ofstream & outputFile, std::vector<unsigned char> & inputBytes);

	//Converts a vector of bytes to the wistringstream
	YOL_ENGINE_API void BytesToWSS(const std::vector<unsigned char> & inputBytes, std::wstringstream & outputWSS);

	//Converts a vector of bytes and returns wistringstream
	YOL_ENGINE_API std::wstringstream BytesToWSS(const std::vector<unsigned char> & inputBytes);

	//Reads file contents to the wistringstream
	YOL_ENGINE_API void FileToWSS(std::wifstream & inputFile, std::wstringstream & outputWSS);

	//Reads file contents and returns wistringstream
	YOL_ENGINE_API std::wstringstream FileToWSS(std::wifstream & inputFile);

	//Obfuscates sequence of bytes with the given key and outputs directly to the output vector
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	YOL_ENGINE_API void ObfuscateBytes(const std::vector<unsigned char> & inputBytes, const std::wstring & key, std::vector<unsigned char> & outputBytes);

	//Deobfuscates sequence of bytes with the given key and outputs directly to the output vector
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	YOL_ENGINE_API void DeobfuscateBytes(const std::vector<unsigned char> & inputBytes, const std::wstring & key, std::vector<unsigned char> & outputBytes);

	//Obfuscates sequence of bytes with the given key and returns vector of bytes
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	YOL_ENGINE_API std::vector<unsigned char> ObfuscateBytes(const std::vector<unsigned char> & inputBytes, const std::wstring & key);

	//Deobfuscates sequence of bytes with the given key and returns vector of bytes
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	YOL_ENGINE_API std::vector<unsigned char> DeobfuscateBytes(const std::vector<unsigned char> & inputBytes, const std::wstring & key);


	//Sets a color of the console (only for the symbols that printed)
	YOL_ENGINE_API void SetColor(const __ConsoleColor & text, const __ConsoleColor & background);

	//Sets a size of the console window. It is also possible to enable/disable scroll
	YOL_ENGINE_API void SetConsoleWindowSize(const unsigned int & width, const unsigned int & height, const bool & isScrollVisible = false);

	//Updates only changed region
	YOL_ENGINE_API void GotoXY(const int & x, const int & y);

	//Clears console withoug using system()
	YOL_ENGINE_API void ClearConsole();

	//Returns inverted color
	YOL_ENGINE_API __ConsoleColor GetInvertedColor(const __ConsoleColor & originalColor);

	//Returns grayscaled color
	YOL_ENGINE_API __ConsoleColor GetGrayscaleColor(const __ConsoleColor & originalColor);


	//Check for file's or folder's existance
	YOL_ENGINE_API bool FileExists(const std::string & file);


	#ifdef _WIN32
		//Returns HWID of the device
		YOL_ENGINE_API std::string GetHWID(const bool & putBrackets = true);

		//Returns full path to the file including name
		YOL_ENGINE_API std::string GetFilePath(const std::string & file);
	#else
		//Returns full path to the file including name
		std::string GetFilePath(const std::string & file);

		//Returns CPU Serial Number
		YOL_ENGINE_API std::string GetPSN();

		//Replacement for windows _getch()
		YOL_ENGINE_API int _getwch();
	#endif


	//Returs amount of digits in a number
	YOL_ENGINE_API inline int GetNumberOfDigits(const int & number) { return number > 0 ? (int)log10((double)number) + 1 : 1; }

	//Returns if two values with floating point are equal or not
	YOL_ENGINE_API inline bool isEqualD(const double & a, const double & b) { return fabs(a - b) < std::numeric_limits<double>::epsilon(); }
	YOL_ENGINE_API inline bool isEqualF(const float & a, const float & b) { return fabs(a - b) < std::numeric_limits<float>::epsilon(); }
}

#endif
