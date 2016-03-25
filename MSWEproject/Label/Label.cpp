#include "Label.h"
#include <iostream>

Label::Label(int x, int y, string str) {
	c = { (short)x, (short)y };
	labelStr = str;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	createLabel();
}

void Label::createLabel() {

	//change curser position
	SetConsoleCursorPosition(handle, c);

	//foreground color
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttr);

	//cursor size
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);

	//print the label
	cout << labelStr;
 }

Label::~Label(){}
