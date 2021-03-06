#include "ComboBox.h"
#define _CRT_SECURE_NO_WARNINGS 

int coloredLine;
int backgroundLine;
DWORD regularAttr;

ComboBox::ComboBox(int x, int y, char* options[], int size) :
	IController(x, y) {

	//handle = GetStdHandle(STD_OUTPUT_HANDLE);
	//defualt text width
	width = 15;
	coloredLine = -1;
	backgroundLine = -1;
	//set in the request position
	//c = { (short)x, (short)y };

	//cursor size
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);

	//dynamic allocations
	choosen = (char*)calloc(width, sizeof(char));
	listSize = size;
	list = (char**)calloc(size, sizeof(char*));
	int i;
	for (i = 0; i < size; i++) {
		list[i] = (char*)calloc(width, sizeof(char));
		strcpy_s(list[i], width, options[i]);
	}
	//init parameters
	isOpen = false;
}


ComboBox::~ComboBox() {
	//free allocation
	free(choosen);
	int i;
	for (i = 0; i < listSize; i++) {
		free(list[i]);
	}
}

void ComboBox::draw() {

	int i, j;
	boolean endFlag;

	//initialize the top box 
	SetConsoleCursorPosition(handle, c);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	regularAttr = cbi.wAttributes;
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	for (i = 0; i < width - 1; i++) {
		choosen[i] = ' ';
		printf("%c", choosen[i]);
	}
	wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	SetConsoleTextAttribute(handle, wAttr2);
	choosen[width] = '>';
	printf("%c", choosen[width]);

	//set char ' ' for the printing(on the rest of the options)
	for (i = 0; i < listSize; i++) {
		endFlag = false;
		for (j = 0; j < width; j++) {
			if (list[i][j] == '\0' || endFlag == true) {
				list[i][j] = ' ';
				endFlag = true;
			}
		}
		endFlag = false;
	}
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
void ComboBox::chooseOption(int position, int lastColoredLine) {
	int listNum = position / 2 - 1 , i;
	SetConsoleCursorPosition(handle, c);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	for (i = 0; i < width - 1; i++) {
		choosen[i] = list[listNum][i];
		printf("%c", choosen[i]);
	}
	setSelected(lastColoredLine);
}

void ComboBox::setSelected(int lastColoredLine) {
	printOption(lastColoredLine * 2 + 2, lastColoredLine);
	printOption(coloredLine * 2 + 2, coloredLine);
}

//print delimiter '-' all over the requested line (separate each option)
void ComboBox::printDelimiter(int position) {
	COORD newCoord = { c.X, c.Y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (i = 0; i < width; i++) {
		printf("-");
	}
}

//print the option
void ComboBox::printOption(int position, int itemNum) {
	COORD newCoord = { c.X, c.Y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (i = 0; i < width; i++) {
		printf("%c", list[itemNum][i]);
	}
}

void ComboBox::printOptionHoverd(int position, int lastBackgroundLine) {
	int lastPos = lastBackgroundLine * 2 + 2, i;
	COORD newCoord = { c.X, c.Y + (short)position };
	COORD lastCoord = { c.X, c.Y + (short)lastPos };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	DWORD wAttr = BACKGROUND_INTENSITY;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	if (backgroundLine == lastBackgroundLine) {
		return;
	}
	else {
		SetConsoleTextAttribute(handle, wAttr);
		//set hover on the new position
		for (i = 0; i < width; i++) {
			printf("%c", list[backgroundLine][i]);
		}
		//if (lastPos == 0) return;
		SetConsoleCursorPosition(handle, lastCoord);
		SetConsoleTextAttribute(handle, regularAttr);
		//set non hover on the last position
		for (i = 0; i < width; i++) {
			printf("%c", list[lastBackgroundLine][i]);
		}
	}
}

//print ' ' (space) for the hiding functioallity
void ComboBox::printSpace(int position) {

	COORD newCoord = { c.X, c.Y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (i = 0; i < width; i++) {
		printf(" ");
	}
}

//listening for any mouse click and handle if relevnt
void ComboBox::handleInput(INPUT_RECORD iRecord) {
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
		//Left button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			checkClickedPosition(mer.dwMousePosition);
		}
		break;
	case MOUSE_MOVED:
		//Mouse moved
		if (!isOpen) return;
		setHover(mer.dwMousePosition);
		break;
	}
}

void ComboBox::setHover(COORD dwMousePosition) {
	int x = dwMousePosition.X, y = dwMousePosition.Y,
			i, lastBackgroundLine;

	if (x >= c.X + 2 && x <= c.X + 15 && y >= c.Y && y <= c.Y + listSize * 2) {
		for (i = 2; i <= 2 * listSize; i += 2) {
			if (dwMousePosition.Y == c.Y + i) {
				lastBackgroundLine = backgroundLine;
				backgroundLine = i / 2 - 1;
				if (lastBackgroundLine == -1) lastBackgroundLine = 0;
				printOptionHoverd(i, lastBackgroundLine);
			}
		}
	}
}

//check if the clicked is relevant for this combo box.
//if yes - check the click position and choose the right operation
void ComboBox::checkClickedPosition(COORD dwMousePosition) {
	int lastColoredLine;

	if (dwMousePosition.X == c.X + width - 1 && dwMousePosition.Y == c.Y) {
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
		for (int i = 2; i <= 2 * listSize; i += 2) {
			if (dwMousePosition.Y == c.Y + i) {
				lastColoredLine = coloredLine;
				coloredLine = i / 2 - 1;
				if (lastColoredLine == -1) lastColoredLine = 0;
				chooseOption(i, lastColoredLine);
			}
		}
	}
}