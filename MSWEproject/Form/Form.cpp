#include "Form.h"



Form::Form()
{
}


bool Form::checkFreeSpace(Panel* panel) {

	return true;
}

int Form::getFocusedPanel() {
	if (panels.size() == 0) return -1;
	for (int i = 0; i < panels.size(); i++) {
		if (panels[i]->isFocus) return i;
	}
}

bool Form::addPanel(Panel* panel) {
	if (!checkFreeSpace(panel)) return false;
	if (panels.size() == 0) panel->isFocus = true;
	panels.push_back(panel);
}

void Form::draw() {
	for (int i = 0; i < panels.size(); i++) panels[i]->draw();
}

void Form::run() {
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

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
			panels[0]->handleInput(irInBuf[i]);
			//if (!panels[0]->handleInput(irInBuf[i]))
				//focusOnNextPanel();
		}
	}

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
}

void Form::ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}

Form::~Form()
{
	for (int i = 0; i < panels.size(); i++) {
		free(panels[i]);
	}
}
