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

	string *options = new string[4];
	options[0] = "This is the first option";
	options[1] = "This is the second option";
	options[2] = "This is the third option";
	options[3] = "This is the fourth option";



	RadioMaster *radioMaster = new RadioMaster(options, 4);

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
		{
			switch (irInBuf[i].EventType)
			{
			case KEY_EVENT: // keyboard input 
				radioMaster->checkEvetnKey(irInBuf[i]);
				break;

			case MOUSE_EVENT: // mouse input 
				radioMaster->mouseEventProc(irInBuf[i].Event.MouseEvent);
				break;


			case FOCUS_EVENT:  // disregard focus events 

			case MENU_EVENT:   // disregard menu events 
				break;

			default:
				ErrorExit("Unknown event type");
				break;
			}
		}
	}
}



void ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}


