#include <iostream>
#include "RadioMaster.h"
#include <Windows.h>


using namespace std;

HANDLE hStdin;
HANDLE hStdout;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR);


int main(void) {

	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	INPUT_RECORD irInBuf[128];

	DWORD cNumRead;

	vector<string> itemsOptions = vector<string>({ "This is the first option", 
		"This is the second option", 
		"This is the third option",
		"This is the fourth option"});

	//RadioMaster *radioMaster = new RadioMaster(options, 4);
	//RadioMaster *radioMaster = new RadioMaster(itemsOptions);
	//radioMaster->draw();

	IController *radioMaster = new RadioMaster(itemsOptions.size(), 20, itemsOptions);
	radioMaster->draw();


	while (1)
	{
		// Wait for the events. 

		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 

		for (int i = 0; i < cNumRead; i++)
			radioMaster->handleInput(irInBuf[i]);
	}
}



void ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}


