////////////////////////////////////////////////////////////////
//                                                            //
//      Utils.cpp                                             //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#include "../include/Utils.h"

using namespace std;
using namespace ConsoleEngine;

// Sets the color of the output
/*
void _Utils::SetColor(const ConsoleEngine::Color & c)
{
#ifdef _WIN32
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((c.background() << 4) | c.foreground()));
#else
    cout << VK_ESCAPE_CHAR;
    switch (c.foreground())
    {
    case cBlack: cout << "[30m"; break;
    case cBlue: cout << "[34m"; break;
    case cGreen: cout << "[32m"; break;
    case cCyan: cout << "[36m"; break;
    case cRed: cout << "[31m"; break;
    case cMagenta: cout << "[35m"; break;
    case cBrown: cout << "[33m"; break;
    case cLightGray: cout << "[37m"; break;
    case cGray: cout << "[90m"; break;
    case cLightBlue: cout << "[94m"; break;
    case cLightGreen: cout << "[92m"; break;
    case cLightCyan: cout << "[96m"; break;
    case cLightRed: cout << "[91m"; break;
    case cLightMagenta: cout << "[95m"; break;
    case cYellow: cout << "[93m"; break;
    case cWhite: cout << "[97m"; break;
    }

    cout << VK_ESCAPE_CHAR;
    switch (c.background())
    {
    case cBlack: cout << "[40m"; break;
    case cBlue: cout << "[44m"; break;
    case cGreen: cout << "[42m"; break;
    case cCyan: cout << "[46m"; break;
    case cRed: cout << "[41m"; break;
    case cMagenta: cout << "[45m"; break;
    case cBrown: cout << "[43m"; break;
    case cLightGray: cout << "[47m"; break;
    case cGray: cout << "[100m"; break;
    case cLightBlue: cout << "[104m"; break;
    case cLightGreen: cout << "[102m"; break;
    case cLightCyan: cout << "[106m"; break;
    case cLightRed: cout << "[101m"; break;
    case cLightMagenta: cout << "[105m"; break;
    case cYellow: cout << "[103m"; break;
    case cWhite: cout << "[107m"; break;
    }
#endif
}
*/
// Crashes the program instantly
void _Utils::Crash(const std::string & reason)
{
    //SetColor(Color(cLightRed, cBlack));
    cout << reason << endl;
    //SetColor(Color(cLightGray, cBlack));
    exit(1);
}
