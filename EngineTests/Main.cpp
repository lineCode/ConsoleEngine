//#include <vld.h>
//#define CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>
#include <conio.h>
#include "YOLConsoleEngineMain.h"

using namespace std;
using namespace YOLConsoleEngine;

int main()
{
	//Now entire __Project object is held as a shared_ptr
	std::shared_ptr<__Project> game = make_shared<__Project>(__Location(L"EngineCore/EngineTestsSettings.ytf"), L"EncryptionKey");
	
	__Form fr(game, __Location(L"EngineCore/UI/Forms/form.ytf"));

	fr.Draw();
	while (true)
		fr.Update(_getwch());
		
	//_CrtDumpMemoryLeaks();	
	_getch();
	return 0;
}