#define _CRT_SECURE_NO_WARNINGS 
#include "ComboBox.h"



ComboBox::ComboBox(int x, int y, char* options[], int size) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//defualt text width
	width = 15;

	//set in the request position
	c = { (short)x, (short)y };

	//cursor size
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);

	//dynamic allocations
	choosen = (char*)calloc(width, sizeof(char));
	listSize = size;
	list = (char**) calloc(size, sizeof(char*));
	for (int i = 0; i < size; i++) {
		list[i] = (char*)calloc(width, sizeof(char));
		strcpy(list[i], options[i]);
	}

	//init parameters
	isOpen = false;
	init();
}


ComboBox::~ComboBox() {
	//free allocation
	free(choosen);
	for (int i = 0; i < listSize; i++) {
		free(list[i]);
	}
}

void ComboBox::init() {

	//initialize the top box 
	SetConsoleCursorPosition(handle, c);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	regularAttr = cbi.wAttributes;
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	for (int i = 0; i < width-1; i++) {
		choosen[i] = ' ';
		printf("%c", choosen[i]);
	}
	wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	SetConsoleTextAttribute(handle, wAttr2);
	choosen[width] = '>';
	printf("%c", choosen[width]);

	//set char ' ' for the printing(on the rest of the options)
	for (int i = 0; i < listSize; i++) {
		boolean endFlag = false;
		for (int j = 0; j < width; j++) {
			if (list[i][j] == '\0' || endFlag == true) {
				list[i][j] = ' ';
				endFlag = true;
			}
		}
		endFlag = false;
	}

	showOptions();
	chooseOption(8);

	//hideOptions();
	//showOptions();
	//chooseOption(2);
}


//show the options - printing them in the correct position
void ComboBox::showOptions() {
	int i;
	for (i = 0; i < listSize; i++) {
		printDelimiter(i * 2 + 1);
		printOption(i * 2 + 2, i);
	}
	printDelimiter(i * 2 + 1);
}

//hide the options - printing ' ' in the correct position
void ComboBox::hideOptions() {
	int i;
	for (i = 1; i <= 2 * listSize + 1; i++) {
		printSpace(i);
	}
}

//printing the requested option to the top box
void ComboBox::chooseOption(int top) {
	int listNum = top/2 - 1;
	SetConsoleCursorPosition(handle, c);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	for (int i = 0; i < width - 1; i++) {
		choosen[i] = list[listNum][i];
		printf("%c", choosen[i]);
	}
}

//print delimiter '-' all over the requested line (separate each option)
void ComboBox::printDelimiter(int top){
	COORD newCoord = { c.X, c.Y + (short)top };
	SetConsoleCursorPosition(handle, newCoord);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (int i = 0; i < width; i++) {
		printf("-");
	}
}

//print the option
void ComboBox::printOption(int top, int itemNum) {
	COORD newCoord = { c.X, c.Y + (short)top };
	SetConsoleCursorPosition(handle, newCoord);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (int i = 0; i < width; i++) {
		printf("%c", list[itemNum][i]);
	}
}

//print ' ' (space) for the hiding functioallity
void ComboBox::printSpace(int top) {
	COORD newCoord = { c.X, c.Y + (short)top };
	SetConsoleCursorPosition(handle, newCoord);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (int i = 0; i < width; i++) {
		printf(" ");
	}
}

//listening for any mouse click and handle if relevnt
void ComboBox::handleInput(INPUT_RECORD iRecord) {
	//if (!isClicked) return;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (iRecord.EventType)
	{
	case MOUSE_EVENT: // mouse input 
		MouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		break;
	}
}

void ComboBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Right button press
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
			checkClickedPosition(mer.dwMousePosition);
		}
		break;
	}
}

//check if the clicked is relevant for this combo box.
//if yes - check the click position and choose the right operation
void ComboBox::checkClickedPosition(COORD dwMousePosition) {
	if (dwMousePosition.X == c.X + width && dwMousePosition.Y == c.Y) {
		if (isOpen == true) {
			isOpen = false;
			hideOptions();
		}
		else {
			isOpen = true;
			showOptions();
		}
	}
	else if (dwMousePosition.X >= c.X && dwMousePosition.X < c.X + width) {
		for (int i = 2; i <= 2 * listSize; i+=2) {
			if (dwMousePosition.Y == c.Y + i) {
				chooseOption(i);
			}
		}
	}
}