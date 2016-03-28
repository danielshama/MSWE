
#include <iostream>
#include "RadioMaster.h"
#include <Windows.h>


using namespace std;

HANDLE hStdin;
HANDLE hStdout;
DWORD fdwSaveOldMode;

void ErrorExit(LPSTR);

void MouseEventProc(MOUSE_EVENT_RECORD mer, RadioMaster *master);
void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

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
				if (irInBuf[i].Event.KeyEvent.bKeyDown) {
					if (irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_UP) {
						radioMaster->goUp();
					}
					if (irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_DOWN) {
						radioMaster->goDown();
					}
					if (irInBuf[i].Event.KeyEvent.wVirtualKeyCode == VK_RETURN) {
						radioMaster->markHovered();
					}
				}
				break;

			case MOUSE_EVENT: // mouse input 
				MouseEventProc(irInBuf[i].Event.MouseEvent, radioMaster);
				break;

			case WINDOW_BUFFER_SIZE_EVENT: // scrn buf. resizing 
				ResizeEventProc(irInBuf[i].Event.WindowBufferSizeEvent);
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

void MouseEventProc(MOUSE_EVENT_RECORD mer, RadioMaster *master) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Left button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			SHORT yPosition = mer.dwMousePosition.Y;
			if (yPosition >= master->getTopY() && yPosition <= master->getBottomY()) {
				master->markHovered();
			}
			//checkClickedPosition(mer.dwMousePosition);
		}
		break;
	case MOUSE_MOVED:
		//Right button press

		SHORT yPosition = mer.dwMousePosition.Y;
		if (yPosition >= master->getTopY() && yPosition <= master->getBottomY()) {
			master->setHoverBackground(yPosition);
		}
		//setHover(mer.dwMousePosition);
		break;
	}
}

void ErrorExit(LPSTR lpszMessage)
{
	fprintf(stderr, "%s\n", lpszMessage);

	// Restore input mode on exit.

	SetConsoleMode(hStdin, fdwSaveOldMode);

	ExitProcess(0);
}

void ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD wbsr)
{
	printf("Resize event\n");
	printf("Console screen buffer is %d columns by %d rows.\n", wbsr.dwSize.X, wbsr.dwSize.Y);
}
