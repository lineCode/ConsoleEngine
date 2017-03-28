/* YOLF.cpp - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
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


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Reads file contents into the vector of bytes (requires file with UTF-16 Big Endian encoding)
	void ReadFileBytes(std::ifstream & inputFile, std::vector<unsigned char> & outputBytes)
	{
		inputFile.seekg(0);

		//Read bytes into vector
		while (!inputFile.eof())
			outputBytes.push_back((unsigned char)(inputFile.get()));

		//Remove eof byte
		outputBytes.pop_back();
	}

	//Reads file contents and returns the vector of bytes (requires file with UTF-16 Big Endian encoding)
	std::vector<unsigned char> ReadFileBytes(std::ifstream & inputFile)
	{
		std::vector<unsigned char> outputBytes;
		ReadFileBytes(inputFile, outputBytes);
		return outputBytes;
	}

	//Writes bytes into the file (requires bytes in UTF-16 Big Endian encoding)
	void WriteFileBytes(std::ofstream & outputFile, std::vector<unsigned char>& inputBytes)
	{
		outputFile.seekp(0);
		for(int i = 0; i < inputBytes.size(); i++)
			outputFile.put(inputBytes[i]);
	}

	//Converts a vector of bytes to the wistringstream
	void BytesToWSS(const std::vector<unsigned char>& inputBytes, std::wstringstream & outputWSS)
	{
		//If there is an odd number of bytes - cut the last byte out
		for (int i = 0; i < inputBytes.size() + ((inputBytes.size() % 2 == 0) ? 0 : -1); i+=2)
			outputWSS.put(inputBytes[i] * 256 + inputBytes[i+1]);
	}

	//Converts a vector of bytes and returns wistringstream
	std::wstringstream BytesToWSS(const std::vector<unsigned char>& inputBytes)
	{
		std::wstringstream outputWSS;
		BytesToWSS(inputBytes, outputWSS);
		return outputWSS;
	}

	//Read file  of bytes to the wistringstream
	void FileToWSS(std::wifstream & inputFile, std::wstringstream & outputWSS)
	{
		outputWSS << inputFile.rdbuf();
	}

	//Reads file contents and returns wistringstream
	std::wstringstream FileToWSS(std::wifstream & inputFile)
	{
		std::wstringstream outputWSS;
		FileToWSS(inputFile, outputWSS);
		return outputWSS;
	}

	//Obfuscatees sequence of bytes with the given key and outputs directly to the output vector
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	void ObfuscateBytes(const std::vector<unsigned char>& inputBytes, const std::wstring & key, std::vector<unsigned char>& outputBytes)
	{
		//Key cannot be empty
		if (key.empty())
			return;
		
		//Set up two rng with different seeds combinations for shifting byte values
		std::mt19937 RNG1(std::default_random_engine(GetRandomSeed(key))());
		std::uniform_real_distribution<> rngDistr1(128,256);
		std::mt19937 RNG2(std::default_random_engine(GetRandomSeed(key+key))());
		std::uniform_real_distribution<> rngDistr2(1, 100);

		//Randomly shift byte value
		for (int i = 0; i < inputBytes.size(); i++)
		{
			int n = rngDistr1(RNG1);
			outputBytes.push_back((rngDistr2(RNG2) > 50) ? (n - inputBytes[i]) : (inputBytes[i] - (n*rngDistr2(RNG2))));
		}

		//Set another rng to shuffle a vector of bytes
		std::mt19937 RNG3(std::default_random_engine(GetRandomSeed(key + key+key))());
		std::uniform_real_distribution<> rngDistr3(0, outputBytes.size()-1);

		//Swap bytes in the vector. Maximum 262144 of swaps for any data
		for (int i = 0; i < (((outputBytes.size() * outputBytes.size() / 262144) > 0) ? 
							262144 : 
							(outputBytes.size() * outputBytes.size() % 262144)); i++)
		{
			unsigned int p1 = rngDistr3(RNG3), p2 = rngDistr3(RNG3);
			unsigned char byte = outputBytes[p1];
			outputBytes[p1] = outputBytes[p2];
			outputBytes[p2] = byte;
		}
	}

	//Deobfuscatees sequence of bytes with the given key and outputs directly to the output vector
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	void DeobfuscateBytes(const std::vector<unsigned char>& inputBytes, const std::wstring & key, std::vector<unsigned char>& outputBytes)
	{
		//All byte manipulations will affect only output, so we just copy over the input bytes
		outputBytes = inputBytes;

		//rng to ushuffle a vector of bytes
		std::mt19937 RNG3(std::default_random_engine(GetRandomSeed(key + key + key))());
		std::uniform_real_distribution<> rngDistr3(0, outputBytes.size() - 1);

		//Since we need to unshuffle, we first have to store all swapping positions
		//in the vector and then read them backwards
		std::vector<std::pair<unsigned int, unsigned int>> swaps;
		for (int i = 0; i < (((outputBytes.size() * outputBytes.size() / 262144) > 0) ?
			262144 :
			(outputBytes.size() * outputBytes.size() % 262144)); i++)
		{
			swaps.push_back({ rngDistr3(RNG3),rngDistr3(RNG3) });
		}

		//Actual unshuffling. Read swap positions from the end to swap bytes in the
		//right order
		for (int i = swaps.size() -1; i >= 0 ; i--)
		{
			unsigned char byte = outputBytes[swaps[i].first];
			outputBytes[swaps[i].first] = outputBytes[swaps[i].second];
			outputBytes[swaps[i].second] = byte;
		}

		//Set up two rng with different seeds combinations for unshifting byte values
		std::mt19937 RNG1(std::default_random_engine(GetRandomSeed(key))());
		std::uniform_real_distribution<> rngDistr1(128, 256);
		std::mt19937 RNG2(std::default_random_engine(GetRandomSeed(key + key))());
		std::uniform_real_distribution<> rngDistr2(1, 100);

		//Unshift randomly shifted byte values
		for (int i = 0; i < outputBytes.size(); i++)
		{
			int  n1 = rngDistr1(RNG1);
			//Since output vector already contains data from input vector we just
			//rewrite vector elements
			outputBytes[i] = (rngDistr2(RNG2) > 50) ? (n1 - outputBytes[i]) : (outputBytes[i] + (n1*rngDistr2(RNG2)));
		}
	}

	//Obfuscatees sequence of bytes with the given key and returns vector of bytes
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	std::vector<unsigned char> ObfuscateBytes(const std::vector<unsigned char>& inputBytes, const std::wstring & key)
	{
		std::vector<unsigned char> outputBytes;
		ObfuscateBytes(inputBytes, key, outputBytes);
		return outputBytes;
	}

	//Deobfuscatees sequence of bytes with the given key and returns vector of bytes
	//NOTE: this is in no way cryptographically secure and should never be used 
	//for serious data encryption. This only prevents project assets from decompilation
	std::vector<unsigned char> DeobfuscateBytes(const std::vector<unsigned char>& inputBytes, const std::wstring & key)
	{
		std::vector<unsigned char> outputBytes;
		DeobfuscateBytes(inputBytes, key, outputBytes);
		return outputBytes;
	}

	//Sets a color of the console (only for the symbols that printed)
	void SetColor(const __ConsoleColor & text, const __ConsoleColor & background)
	{
		#ifdef _WIN32
			//Gets console window handler
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			//Sets console text attributes
			SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
		#else
			switch(text)
			{
				case cBlack: std::wcout << L"\033[30m"; break;
				case cBlue: std::wcout << L"\033[34m"; break;
				case cGreen: std::wcout << L"\033[32m"; break;
				case cCyan: std::wcout << L"\033[36m"; break;
				case cRed: std::wcout << L"\033[31m"; break;
				case cMagenta: std::wcout << L"\033[35m"; break;
				case cBrown: std::wcout << L"\033[33m"; break;
				case cLightGray: std::wcout << L"\033[37m"; break;
				case cDarkGray: std::wcout << L"\033[90m"; break;
				case cLightBlue: std::wcout << L"\033[94m"; break;
				case cLightGreen: std::wcout << L"\033[92m"; break;
				case cLightCyan: std::wcout << L"\033[96m"; break;
				case cLightRed: std::wcout << L"\033[91m"; break;
				case cLightMagenta: std::wcout << L"\033[95m"; break;
				case cYellow: std::wcout << L"\033[93m"; break;
				case cWhite: std::wcout << L"\033[97m"; break;
			}

			switch(background)
			{
				case cBlack: std::wcout << L"\033[40m"; break;
				case cBlue: std::wcout << L"\033[44m"; break;
				case cGreen: std::wcout << L"\033[42m"; break;
				case cCyan: std::wcout << L"\033[46m"; break;
				case cRed: std::wcout << L"\033[41m"; break;
				case cMagenta: std::wcout << L"\033[45m"; break;
				case cBrown: std::wcout << L"\033[43m"; break;
				case cLightGray: std::wcout << L"\033[47m"; break;
				case cDarkGray: std::wcout << L"\033[100m"; break;
				case cLightBlue: std::wcout << L"\033[104m"; break;
				case cLightGreen: std::wcout << L"\033[102m"; break;
				case cLightCyan: std::wcout << L"\033[106m"; break;
				case cLightRed: std::wcout << L"\033[101m"; break;
				case cLightMagenta: std::wcout << L"\033[105m"; break;
				case cYellow: std::wcout << L"\033[103m"; break;
				case cWhite: std::wcout << L"\033[107m"; break;
			}
			
		#endif
	}

	//Sets a size of the console window. It is also possible to enable/disable scroll
	void SetConsoleWindowSize(const unsigned int & width, const unsigned int & height, const bool & isScrollVisible)
	{
		#ifdef _WIN32
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			CONSOLE_SCREEN_BUFFER_INFO bufferInfo;
			GetConsoleScreenBufferInfo(h, &bufferInfo);
			SMALL_RECT& winInfo = bufferInfo.srWindow;
			COORD windowSize = { winInfo.Right - winInfo.Left + 1, winInfo.Bottom - winInfo.Top + 1 };

			if (windowSize.X > width || windowSize.Y > height)
			{
				SMALL_RECT info = {	0, 0, width < windowSize.X ? width - 1 : windowSize.X - 1,
									height < windowSize.Y ? height - 1 : windowSize.Y - 1 };
				SetConsoleWindowInfo(h, TRUE, &info);
			}

			COORD size = { width, height };
			if (isScrollVisible)
				size.Y = 9999;

			SetConsoleScreenBufferSize(h, size);
			SMALL_RECT info = { 0, 0, width - 1, height - 1 };
			SetConsoleWindowInfo(h, TRUE, &info);
		#else
			std::wcout << "\e[8;" << height << ";" << width << "t";
		#endif
	}

	//Updates only changed region
	void GotoXY(const int & x, const int & y)
	{
		#ifdef _WIN32
			COORD coord{ x,y };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		#else
			std::wcout << "\33[" << y << ";" << x <<"H";
		#endif
	}

	//Clears console withoug using system()
	void ClearConsole()
	{
		#ifdef _WIN32
			HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
			COORD coord = { 0, 0 };
			DWORD count;
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			if (GetConsoleScreenBufferInfo(hStdOut, &csbi))
			{
				FillConsoleOutputCharacter(hStdOut, (TCHAR)32, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
				FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, csbi.dwSize.X * csbi.dwSize.Y, coord, &count);
				SetConsoleCursorPosition(hStdOut, coord);
			}
		#else
			std::wcout << "\033[H\033[J";
		#endif
	}

	//Returns inverted color
	__ConsoleColor GetInvertedColor(const __ConsoleColor & originalColor)
	{
		if (originalColor == cTransparent)
			return __ConsoleColor::cTransparent;

		return __ConsoleColor(15 - originalColor);
	}

	//Returns grayscaled color
	__ConsoleColor GetGrayscaleColor(const __ConsoleColor & originalColor)
	{
		switch (originalColor)
		{
		//All Black
		case 0:
		case 1:
		case 4:
		case 5:
			return __ConsoleColor::cBlack;

		//All Dark gray
		case 2:
		case 3:
		case 8:
		case 9:
			return __ConsoleColor::cDarkGray;

		//All Light gray
		case 6:
		case 7:
		case 12:
		case 13:
			return __ConsoleColor::cLightGray;

		//All white
		case 10:
		case 11:
		case 14:
		case 15:
			return __ConsoleColor::cWhite;

		default: 
			return __ConsoleColor::cTransparent;
		}
	}

	//Check for file's or folder's existance
	//Returns true if found, else false
	bool FileExists(const std::string & file)
	{
		struct stat buf;
		return (stat(file.c_str(), &buf) == 0);
	}

	#ifdef _WIN32
		//Returns HWID of the device
		std::string GetHWID(const bool & putBrackets)
		{
			HW_PROFILE_INFOW hwProfileInfo;

			GetCurrentHwProfileW(&hwProfileInfo);
			std::wstring wc = hwProfileInfo.szHwProfileGuid;

			std::string HWID(wc.begin(),wc.end());

			if (!putBrackets)
				HWID.assign(HWID, 1, HWID.size() - 2);

			return HWID;
		}

		//Returns full path to the file including name
		std::string GetFilePath(const std::string & file)
		{
			char fullPathBuf[MAX_PATH];
			GetFullPathNameA(file.c_str(), MAX_PATH, fullPathBuf, NULL);
			return std::string(fullPathBuf);
		}
	#else
		//Returns full path to the file including name
		std::string GetFilePath(const std::string & file)
		{ 
			if(realpath(file.c_str(), NULL) != nullptr)
				return std::string(realpath(file.c_str(), NULL));

			return std::string(); 
		}

		//Replacement for windows _getch()
		int _getwch(void)
		{
			struct termios oldattr, newattr;
			int ch;
			tcgetattr( STDIN_FILENO, &oldattr );
			newattr = oldattr;
			newattr.c_lflag &= ~( ICANON | ECHO );
			tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
			ch = getwchar();
			tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
			return ch;
		}

		//Returns CPU Serial Number
		std::string GetPSN()
		{
			char * psn;
			int varEAX, varEBX, varECX, varEDX;
			char str[9];

			__asm__ __volatile__("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (1));
			sprintf(str, "%08X", varEAX);
			sprintf(psn, "%C%C%C%C-%C%C%C%C", str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
			__asm__ __volatile__("cpuid"   : "=a" (varEAX), "=b" (varEBX), "=c" (varECX), "=d" (varEDX) : "a" (3));
			sprintf(str, "%08X", varEDX);
			sprintf(psn, "%s-%C%C%C%C-%C%C%C%C", psn, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);
			sprintf(str, "%08X", varECX);
			sprintf(psn, "%s-%C%C%C%C-%C%C%C%C", psn, str[0], str[1], str[2], str[3], str[4], str[5], str[6], str[7]);

			return std::string(psn);
		}
	#endif
}
