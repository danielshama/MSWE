#include "NumericBox.h"


NumericBox::NumericBox(int width, int minimum, int maximum) : IController(width) 
{
	max = maximum;
	min = minimum;
	value = min;
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	regularAttr = cbi.wAttributes;
}



NumericBox::~NumericBox(){}

void NumericBox::draw() 
{
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	DWORD white = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	SetConsoleTextAttribute(handle, white);
	cout << '-';
	SetConsoleTextAttribute(handle, regularAttr);
	cout << " " << value << " ";
	SetConsoleTextAttribute(handle, white);
	cout << '+';
}

void NumericBox::handleInput(INPUT_RECORD iRecord) {
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

void NumericBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
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
	}
}

void NumericBox::checkClickedPosition(COORD dwMousePosition) {

	if (dwMousePosition.X == loc.x && dwMousePosition.Y == loc.y) {
		changeValue(-1);
	}
	else if (dwMousePosition.X == loc.x + 5 && dwMousePosition.Y == loc.y) {
		changeValue(1);
	}
}

void NumericBox::changeValue(int add) {
	if (value + add < min) return;
	else if (value + add > max) return;
	value += add;
	draw();
}

int NumericBox::GetValue() {
	return value;
}

bool NumericBox::SetValue(int val) {
	if (val < min || val > max) return false;
	value = val;
	draw();
	return true;
}

void NumericBox::setMin(int m){
	min = m; 
	value = min;
	draw();
}

void NumericBox::setMax(int m){
	max = max;
	value = min;
	draw();
}