#include "Button.h"

Button::Button(int width) : IController(width)
{
	loc.height = 1;
	isFocusable = false;
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
}


Button::~Button()
{
}


void Button::draw() 
{
	//change curser position
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	//foreground color
	DWORD wAttr = FOREGROUND_GREEN | BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttr);
	
	//print the Button
	string buttonFrame;
	for (int i = 0; i < loc.width; i++) buttonFrame += " ";
	for (short i = 1; i < 4; i++) {
		cout << buttonFrame;
		SetConsoleCursorPosition(handle, { loc.x, loc.y+i });
	}
	SetConsoleCursorPosition(handle, { loc.x + (short)(loc.width - buttonStr.length())/2, loc.y + 1 });
	cout << buttonStr;

}

void Button::setText(string value) {
	buttonStr = value;
}