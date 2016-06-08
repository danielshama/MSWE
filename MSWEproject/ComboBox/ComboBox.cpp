#include "ComboBox.h"
#define _CRT_SECURE_NO_WARNINGS 


ComboBox::ComboBox(int width, vector<string> entries) :
	IController(width) {
	loc.x = 10;
	loc.y = 10;
	loc.height = 2 + 2 * (int)entries.size();

	coloredLine = -1;
	backgroundLine = -1;
	choosen = entries[0];
	//cursor size
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	regularAttr = cbi.wAttributes;
	list = entries;

	//init parameters
	listItemOn = 0;
	isOpen = false;
}


ComboBox::~ComboBox() {}

void ComboBox::draw() {

	int i, j;
	boolean endFlag;

	//initialize the top box 
	SetConsoleCursorPosition(handle, { loc.x, loc.y });

	printChoosen();
}

void ComboBox::printChoosen() {
	COORD newCoord = {loc.x, loc.y};
	SetConsoleCursorPosition(handle, newCoord);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	string stringToPrint = choosen + " ";
	for (int i = 0; i < loc.width - choosen.length(); i++) {
		stringToPrint += " ";
	}
	cout << stringToPrint;
	wAttr2 = cbi.wAttributes | BACKGROUND_RED;
	SetConsoleTextAttribute(handle, wAttr2);
	cout << "+";
}


//show the options - printing them in the correct position
void ComboBox::showOptions() {
	int i;
	for (i = 0; i < list.size(); i++) {
		printDelimiter(i * 2 + 1);
		printOption(i * 2 + 2, i);
	}
	printDelimiter(i * 2 + 1);
}

//hide the options - printing ' ' in the correct position
void ComboBox::hideOptions() {
	int i;
	for (i = 1; i <= 2 * list.size() + 1; i++) {
		printSpace(i);
	}
}

//printing the requested option to the top box
void ComboBox::chooseOption(int position, int lastColoredLine) {
	int listNum = position / 2 - 1 , i;
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	choosen = list[listNum];
	printChoosen(); 
	SetSelectedIndex(lastColoredLine);
}

//print delimiter '-' all over the requested line (separate each option)
void ComboBox::printDelimiter(int position) {
	COORD newCoord = { loc.x, loc.y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (i = 0; i < loc.width; i++) {
		printf("-");
	}
}

//print the option
void ComboBox::printOption(int position, int itemNum) {
	COORD newCoord = { loc.x, loc.y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	string item = list[itemNum];
	for (i = 0; i < loc.width - item.length(); i++) {
		item += " ";
	}
	cout << item;
}

void ComboBox::printOptionHoverd(int position, int lastBackgroundLine) {
	listItemOn = backgroundLine;
	int lastPos = lastBackgroundLine * 2 + 2, i;
	COORD newCoord = { loc.x, loc.y + (short)position };
	COORD lastCoord = { loc.x, loc.y + (short)lastPos };
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
		string item = list[backgroundLine];
		for (i = 0; i < loc.width - item.length(); i++) {
			item += " ";
		}
		cout << item;
		//if (lastPos == 0) return;
		SetConsoleCursorPosition(handle, lastCoord);
		SetConsoleTextAttribute(handle, regularAttr);
		//set non hover on the last position
		item = list[lastBackgroundLine];
		for (i = 0; i < loc.width - item.length(); i++) {
			item += " ";
		}
		cout << item;
	}
}

//print ' ' (space) for the hiding functioallity
void ComboBox::printSpace(int position) {

	COORD newCoord = { loc.x, loc.y + (short)position };
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	int i;

	SetConsoleCursorPosition(handle, newCoord);
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, regularAttr);
	for (i = 0; i < loc.width; i++) {
		printf(" ");
	}
}

void ComboBox::checkKey(int listItem) {
	if (listItem < 0) listItem = list.size()-1;
	if (listItem == list.size()) listItem = 0;
	setHover({ loc.x+2, loc.y + listItem * 2 + 2 });
}

//listening for any mouse click and handle if relevnt
bool ComboBox::handleInput(INPUT_RECORD iRecord) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	bool res = true;
	switch (iRecord.EventType)
	{
	case MOUSE_EVENT: // mouse input 
		MouseEventProc(iRecord.Event.MouseEvent);
		if (!isFocus) res = false;
		break;
	
	case KEY_EVENT: // keyboard input 
		keyEventProc(iRecord.Event.KeyEvent);
		if (!isFocus) res = false;
		break;

	default:
		break;
	}
	return res;
}

void ComboBox::keyEventProc(KEY_EVENT_RECORD ker) {
	if (!isFocus) return;
	if (ker.bKeyDown) {
		if (isOpen) {
			//up key pressed
			if (ker.wVirtualKeyCode == VK_UP) {
				checkKey(--listItemOn);
			}
			//down key pressed
			else if (ker.wVirtualKeyCode == VK_DOWN) {
				checkKey(++listItemOn);
			}
			//UP numpad key pressed
			else if (ker.wVirtualKeyCode == VK_NUMPAD8) {
				checkKey(--listItemOn);
			}
			//Down numpad pressed
			else if (ker.wVirtualKeyCode == VK_NUMPAD2) {
				checkKey(++listItemOn);
			}
			//BACKSPACE key pressed
			else if (ker.wVirtualKeyCode == VK_RETURN) {
				int lastColoredLine = coloredLine;
				coloredLine = listItemOn / 2 - 1;
				if (lastColoredLine == -1) lastColoredLine = 0;
				chooseOption(listItemOn * 2 + 2, lastColoredLine);
				printOption(listItemOn * 2 + 2, listItemOn);
				hideOptions();
				isOpen = false;
			}
		}
		//TAB key pressed
		if (ker.wVirtualKeyCode == VK_TAB) {
			if (isOpen) {
				if (listItemOn == list.size() - 1){
					isFocus = false;
					isOpen = false;
					hideOptions();
				}
				else checkKey(++listItemOn);
			}
			else {
				isFocus = false;
			}
		}
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
		if (!isOpen || !isFocus) return;
		setHover(mer.dwMousePosition);
		break;
	}
}

void ComboBox::setHover(COORD dwMousePosition) {
	int x = dwMousePosition.X, y = dwMousePosition.Y,
			i, lastBackgroundLine;

	if (x >= loc.x + 2 && x <= loc.x + loc.width && y >= loc.y && y <= loc.y + list.size() * 2) {
		isFocus = true;
		for (i = 2; i <= 2 * list.size(); i += 2) {
			if (dwMousePosition.Y == loc.y + i) {
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

	if (dwMousePosition.X == loc.x + loc.width + 1 && dwMousePosition.Y == loc.y) {
		isFocus = true;
		if (isOpen == true) {
			isOpen = false;
			hideOptions();
		}
		else {
			isOpen = true;
			showOptions();
		}
	}
	else if (dwMousePosition.X >= loc.x && dwMousePosition.X < loc.x + loc.width) {
		if (!isOpen) return;
		for (int i = 2; i <= 2 * list.size(); i += 2) {
			if (dwMousePosition.Y == loc.y + i) {
				lastColoredLine = coloredLine;
				coloredLine = i / 2 - 1;
				if (lastColoredLine == -1) lastColoredLine = 0;
				chooseOption(i, lastColoredLine);
			}
		}
	}
	else {
		isFocus = false;
		isOpen = false;
		hideOptions();
	}
}

void ComboBox::SetSelectedIndex(size_t lastColoredLine) {
	//printOption(lastColoredLine * 2 + 2, lastColoredLine);
	//printOption(coloredLine * 2 + 2, coloredLine);
	hideOptions();
	isOpen = false;
}

size_t ComboBox::GetSelectedIndex(){
	for (int i = 0; i < list.size(); i++) {
		if (list[i].compare(choosen) == 0) return i;
	}
	return -1;
}
