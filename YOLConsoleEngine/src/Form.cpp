/* Form.h - Part of the YOLConsoleEngine - v1.0 - HaselLoyance - public domain.
No warranty implied; use at your own risk

Base system for HTML like forms for accepting user input.
Requires a file with instructions in UI/Forms directory

Check documentation of each input type for proper syntax

LICENSE
This software is dual-licensed to the public domain and under the following
license: you are granted a perpetual, irrevocable license to copy, modify,
publish, and distribute this file as you see fit.
*/


//Global include for all YOLConsoleEngine modules
#include "../include/YOLConsoleEngine.h"

namespace YOLConsoleEngine
{
	//Constructor without form file load
	__Form::__Form(const std::shared_ptr<__Project> & pr) : project(pr)
	{
		Init();
	}

	//Constructor with form file load
	__Form::__Form(const std::shared_ptr<__Project> & pr, const __Location & loc) : project(pr)
	{
		//Init() is called in Load()
		Load(loc);
	}

	__Form::~__Form() { }

	//Initializes all variables
	void __Form::Init()
	{
		location = __Location();
		name = std::wstring();
		position = __Vec2();
		keyBack = 0;
		currentActiveInput = 0;
	}

	//Loads all components of the form from given file
	//Also resets all previously set variables
	__EngineErrors __Form::Load(const __Location & loc)
	{
		Init();
		location = loc;

		std::wstringstream formFileStream;
		std::vector<unsigned char> formFileBytes;
		std::wstring formFileLine;

		//Change file location
		if (YOL_ENGINE_DEBUG)
			location = __Location("EngineCoreRaw/" + std::string(loc.filePath, 11, loc.filePath.size() - 14) + "txt");

		//Open form file and get all bytes
		std::ifstream formFileIn(location.filePath, std::ios::binary);
		if (formFileIn.fail())
			return FILE_STREAM_ERROR;

		ReadFileBytes(formFileIn, formFileBytes);
		formFileIn.close();

		//Engine is in release mode - require deobfuscation
		if (!YOL_ENGINE_DEBUG)
			formFileBytes = DeobfuscateBytes(formFileBytes, project->GetProjectKey());

		//File bytes are directly turned into wstringstream
		BytesToWSS(formFileBytes, formFileStream);

		//Read form information from first line
		//<form name> <x> <y> <keyBack>
		std::getline(formFileStream, formFileLine);
		std::wstringstream(formFileLine) >> name >> position.x >> position.y >> keyBack;

		//Parse through the rest of the file to get information about each input
		while (!formFileStream.eof())
		{
			//Skip empty lines
			std::getline(formFileStream, formFileLine);
			if (formFileLine.empty())
				continue;

			if (formFileLine.find(L"INPUT_TEXT") != std::wstring::npos) //INPUT_TEXT input
				input.push_back(std::make_shared<__InputText>(__InputText(project, formFileLine)));
			else if (formFileLine.find(L"INPUT_NUMBER") != std::wstring::npos) //INPUT_NUMBER input
				input.push_back(std::make_shared<__InputNumber>(__InputNumber(project, formFileLine)));
			else if (formFileLine.find(L"INPUT_BUTTON") != std::wstring::npos) //INPUT_SUBMIT input
				input.push_back(std::make_shared<__InputButton>(__InputButton(project, formFileLine)));
		}

		//Obfuscate form file in the EngineCore directory
		std::ofstream formFileOut(loc.path + "/" + loc.fileName + ".ytf", std::ios::binary);
		if (formFileOut.fail())
			return FILE_STREAM_ERROR;

		formFileBytes = ObfuscateBytes(formFileBytes, project->GetProjectKey());
		WriteFileBytes(formFileOut, formFileBytes);

		//Do not allow forms with no input fields
		if (input.size() < 1)
			return FILE_EMPTY;

		return SUCCESS;
	}

	//Goes through each input field and calls Draw() method
	void __Form::Draw()
	{
		for(int i =0; i < input.size(); i++)
			input[i]->Draw(position);

		//Active input is redrawn so the cursor is in the right position
		input[currentActiveInput]->Draw(position);
	}

	//Updates form based on input
	//Returns current active input field
	int __Form::Update(const int & keycode)
	{
		//Enter hit on button input
		if (keycode == VK_RETURN && input[currentActiveInput]->GetType() == L"INPUT_BUTTON") 
		{
			return stoi(input[currentActiveInput]->GetData());
		}
		else if (keycode == VK_TAB) //Goes to the next input field
		{
			//If previous active input is a button - redraw it in normal color
			if (input[currentActiveInput]->GetType() == L"INPUT_BUTTON")
				input[currentActiveInput]->Draw(position);

			if (currentActiveInput++ >= input.size()-1)
				currentActiveInput = 0;

			input[currentActiveInput]->Draw(position);
		}
		else if (keycode == keyBack) //Keyback pressed - go to the prev input field
		{
			//If previous active input is a button - redraw it in normal color
			if (input[currentActiveInput]->GetType() == L"INPUT_BUTTON")
				input[currentActiveInput]->Draw(position);

			if (currentActiveInput-- <= 0)
				currentActiveInput = input.size()-1;
			input[currentActiveInput]->Draw(position);
		}
		else
			input[currentActiveInput]->Update(keycode, position); //Update current active input with the pressed key

		//Buttons have to be held separetely since we have to also undraw them when they
		//are not active
		if (input[currentActiveInput]->GetType() == L"INPUT_BUTTON")
		{
			//Dirty hack that signals to Draw() method to draw button in active color
			//data is resetted afterwards
			input[currentActiveInput]->data.push_back(L'A');
			input[currentActiveInput]->Draw(position);
		}

		return currentActiveInput;
	}
}