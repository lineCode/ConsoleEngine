//#include <vld.h>
//#define CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#include <iostream>

#ifdef _WIN32
	#include <conio.h>
#endif

#include <YOLConsoleEngine.h>

using namespace std;
using namespace YOLConsoleEngine;

int main()
{
	//Now entire __Project object is held as a shared_ptr
	std::shared_ptr<__Project> game = make_shared<__Project>(__Location("EngineCore/EngineTestsSettings.ytf"), L"EncryptionKey");


	__Form fr(game, __Location("EngineCore/UI/Forms/form.ytf"));

	fr.Draw();
	while (true)
		fr.Update(_getwch());
	
	//_CrtDumpMemoryLeaks();	
	_getwch();

	return 0;
}