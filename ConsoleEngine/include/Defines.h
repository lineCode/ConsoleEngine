////////////////////////////////////////////////////////////////
//                                                            //
//      Defines.h                                             //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#define DBL_EPSILON 2.2204460492503131e-016
#define RAD2DEG 57.29577951308232
#define DEG2RAD 0.017453292519943
#define VAR_NAME(var) #var
#define VAR_TYPE(var) typeid(var).name()
#define MAKE_OBJ_PARAM(var) ObjParam({ VAR_NAME(var), _Utils::AnyToString(var), VAR_TYPE(var) })

#define eBeforeConstruct "BeforeConstruct"
#define eAfterConstruct "AfterConstruct"
#define eBeforeDestruct "BeforeDestruct"
#define eAfterDestruct "AfterDestruct"
#define eChange "Change"
#define eChangeVec2 "ChangeVec2"
#define eChangeX "ChangeX"
#define eChangeY "ChangeY"
#define eChangeColor "ChangeColor"
#define eChangeForeground "ChangeForeground"
#define eChangeBackground "ChangeBackground"
#define eChangeSize "ChangeSize"
#define eChangeScrollbar "ChangeScrollbar"

#if defined(_WIN32) && defined(CONSOLE_ENGINE_DLL)
    #ifdef CONSOLE_ENGINE_EXPORTS
        #define CONSOLE_ENGINE_API __declspec(dllexport)
    #else
        #define CONSOLE_ENGINE_API __declspec(dllimport)
    #endif
#else
	#define CONSOLE_ENGINE_API 
#endif

#ifdef _WIN32
    #include <io.h>
    #include <Windows.h>

    #define VK_ESCAPE_CHAR 0xE0
    #define VK_UP 0x48
    #define VK_DOWN 0x50
    #define VK_RIGHT 0x4D
    #define VK_LEFT 0x4B
#else
    #include <sys/ioctl.h>
    #include <signal.h>
    #include <termios.h>
    #include <unistd.h>

    #define VK_TAB 0x09
    #define VK_RETURN 0x0A
    #define VK_BACK 0x7F
    #define VK_UP 0x41
    #define VK_DOWN 0x42
    #define VK_RIGHT 0x43
    #define VK_LEFT 0x44
    #define VK_ESCAPE_CHAR '\033'
    #define OutputDebugStringW(a) {}
    #define CreateDirectoryA(name, value) mkdir(name, ACCESSPERMS)
#endif
