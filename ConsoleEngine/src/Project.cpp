////////////////////////////////////////////////////////////////
//                                                            //
//      Project.cpp                                           //
//      HaselLoyance 2017, Unlicense                          //
//      https://github.com/HaselLoyance/ConsoleEngine         //
//                                                            //
////////////////////////////////////////////////////////////////

#include "../include/Project.h"

using namespace std;
using namespace ConsoleEngine;


Project::Project()
{
    RunCallback(evBeforeConstruct);
    RunCallback(evAfterConstruct);
}

Project::~Project()
{
    RunCallback(evBeforeDestruct);
    RunCallback(evAfterDestruct);
}
