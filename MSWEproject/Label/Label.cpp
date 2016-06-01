#include "Label.h"

Label::Label(int width) : 
	IController(width) {
	loc.height = 1;
	isFocusable = false;
}


void Label::draw() {

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

void Label::setText(string value) {
	labelStr = value;
}