////////////////////////////////////////////////////////////////
//                                                            //
//      Singleton.h                                           //
//      HaselLoyance 2017, Unlicensed                         //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#ifndef CONSOLE_ENGINE_SINGLETON_H
#define CONSOLE_ENGINE_SINGLETON_H

#include "Defines.h"
#include "Utils.h"

namespace ConsoleEngine
{
    // Restrics class objects creation to one maximum
    template<class DerivedType>
	class _Singleton
	{
	public:

        // Returns pointer to the created instance of this class
        static DerivedType * Instance()
        {
            return _instance;
        }

    protected:
        // At construct checks if pointer is already declared (instance was
        // created), if not - continue, else - crash program, because
        // only one instance of the objects is allowed
        _Singleton()
        {
            if (_instance != nullptr)
            {
                _Utils::Crash("More than one instance exists");
            }

            // Store pointer to the instance
            _instance = static_cast<DerivedType*>(this);
        }
        ~_Singleton() {}

    private:
        // Pointer to the created object singleton
        // Defaults to nullptr
        static DerivedType * _instance;
    };

    template<class DerivedType>
    DerivedType * _Singleton<DerivedType>::_instance = nullptr;
}

#endif
