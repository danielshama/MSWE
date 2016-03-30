#include <windows.h>
#include <stdio.h>
#include "ComboBox.h"

HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	char* arr[] = { "item1", "item2", "item3", "item4" };
	ComboBox comboBox = ComboBox(7, 7, arr, 4);

	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			//Send the input record to the textbox handler
			comboBox.handleInput(irInBuf[i]);
		}
	}

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}

VOID ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}
