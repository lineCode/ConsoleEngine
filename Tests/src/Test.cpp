#include "ConsoleEngine.h"
#include <limits>
#include <fstream>

using namespace std;
using namespace ConsoleEngine;

int main()
{
	srand(time(NULL));
	//uint64_t g = generateLargePrime(32);
	//cout << "Prime is " << g << endl;
	/*
	vector<Object*> objectsStack;

	Object::OnGlobal(eBeforeConstruct, [&objectsStack](auto * c) {
		cout << "Object constructor called. Original stack size: " << objectsStack.size() << endl;
	});

	Object::OnGlobal(eAfterConstruct, [&objectsStack](auto * c) {
		cout << "Object constructor finished. New stack size: " << objectsStack.size() << endl;
	});

	Object::OnGlobal(eBeforeDestruct, [&objectsStack](auto * c) {
		cout << "Object destructor called. Original stack size: " << objectsStack.size() << endl;
	});

	Object::OnGlobal(eAfterDestruct, [&objectsStack](auto * c) {
		cout << "Object destructor finished. New stack size: " << objectsStack.size() << endl;
	});


	{
		Object o(&objectsStack);

		{
			cout << "1 object size is: " << (sizeof(string)) << endl;

			cout << "With 1 object stack size is: " << sizeof(objectsStack) + (sizeof(Object) * objectsStack.size()) << endl;
			cout << "-----" << endl;
			Object o(&objectsStack);
			cout << "With 2 objects stack size is: " << sizeof(objectsStack) + (sizeof(Object) * objectsStack.size()) << endl;
			objectsStack.back()->On(eBeforeDestruct, [](auto) {
				cout << "Destroying second object" << endl;
			});
		}

		objectsStack.back()->On(eBeforeDestruct, [](auto) {
			cout << "Destroying first object" << endl;
		});
	} */

	Project p;
	Project * pp = Project::Instance();

	Display dtemp;
	
	Color c(cBlue, cYellow);
	DisplayTemp d;

	d.Size(Size2(100, 30), true);
	d.Color(c);

	d.On(evChangeSize, [](DisplayTemp * d) {
		cout << "Applied new size: " << d->Size().ToString() << endl;
	});

	d.On(evChangeColor, [](DisplayTemp * d) {
		cout << "(Instance message) Display color changed to " << d->Color().foreground() << "  " << d->Color().background() << endl;
	});


	d._CycleEnd();

	//system("pause");
	return 0;
}
