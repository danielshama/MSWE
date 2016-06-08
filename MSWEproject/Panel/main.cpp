#include "Panel.h"
#include "../Label/Label.h"
#include "../TextBox/TextBox.h"


HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	Panel *panel = new Panel(40, 70);
	panel->setLocation(10, 10);
	Panel *panel2 = new Panel(10, 12);
	Label *label = new Label(10);
	TextBox *textBox = new TextBox(20);
	label->setText("Noam Star");
	//((Panel*)panel)->addControl(panel2, 1, 1);
	panel->addControl(textBox, 5, 5);
	panel->addControl(label, 15, 25);
	panel->draw();

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
			panel->handleInput(irInBuf[i]);
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
