#include "ItemList.h"

ItemList::ItemList(int x, int y, string str) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	coord = { (short)x, (short)y };
	buffer = new char[10];
	isClicked = false;
	isChecked = false;
	lbl = str;
	size = str.length() + 4;
	curserPosition = 0;
}

void ItemList::create() {
	SetConsoleCursorPosition(handle, coord);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);

	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE;
	SetConsoleTextAttribute(handle, wAttr2);
	cout << "[ ] " + lbl << endl;
}


void ItemList::check() {
	DWORD background;

	SetConsoleCursorPosition(handle, coord);
	if (isChecked == false) {

		cout << "[X] " << lbl;

		if (!FillConsoleOutputAttribute(handle,
			BACKGROUND_BLUE | BACKGROUND_RED,
			size, coord, &background)) {
			cout << "failed to change the background" << endl;
			exit(1);
		}
		isChecked = true;
	}
	else {

		cout << "[ ] " << lbl;

		if (!FillConsoleOutputAttribute(handle, BACKGROUND_BLUE, size, coord, &background)) {
			cout << "failed to change the background" << endl;
			exit(1);
		}
		isChecked = false;
	}
}
void ItemList::click() {
	DWORD color;
	if (!isChecked) {
		color = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED; //gray
	}
	else {
		color = BACKGROUND_BLUE | BACKGROUND_GREEN; //green
	}
	DWORD background;
	if (!FillConsoleOutputAttribute(handle, color, size, coord, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	isClicked = true;
}
void ItemList::unclick() {
	DWORD color;
	if (!isChecked) {
		color = BACKGROUND_BLUE;
	}
	else {
		color = BACKGROUND_BLUE | BACKGROUND_RED;
	}
	DWORD background;
	if (!FillConsoleOutputAttribute(handle, color, size, coord, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	isClicked = false;
}

ItemList::~ItemList() {
}
