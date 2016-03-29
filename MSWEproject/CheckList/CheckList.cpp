#include "CheckList.h"

CheckList::CheckList(string opts[], int optAmount, short x, short y){
	amount = optAmount;
	coord = { x,y };
	ifClicked = true;
	options = opts;
	handler = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 50, FALSE };
	SetConsoleCursorInfo(handler, &cci);
	width = 0;
	for (int i = 0; i < amount; i++) {
		if (width < opts[i].length()) width = opts[i].length();
		items.push_back(ItemList(x, y + i, opts[i]));
		items[i].create();
		isChecked.push_back(0);
		isClicked.push_back(0);
	}
	items[1].click();
	isClicked[1] = 1;
}

void CheckList::handleInput(INPUT_RECORD iRecord) {

	if (!ifClicked) return;
	handler = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (iRecord.EventType)
	{
	case KEY_EVENT: // keyboard input 
		keyEventProc(iRecord.Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input 
		MouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		break;
	}
}

void CheckList::keyEventProc(KEY_EVENT_RECORD ker) {
	CONSOLE_SCREEN_BUFFER_INFO ct;
	if (!GetConsoleScreenBufferInfo(handler, &ct))
	{
		cout << "GetConsoleScreenBufferInfo failed" << GetLastError << endl;
		return;
	}
	COORD c = ct.dwCursorPosition;
	if (c.X >= coord.X && 
		c.X <= (coord.X + width) &&
		c.Y >= coord.Y &&
		c.Y <= coord.Y + amount) {

		if (ker.bKeyDown) {
			int item = whoClicked();
			if (item < 0) return;
			//ENTER key pressed
			if (ker.wVirtualKeyCode == VK_RETURN) {
				items[item].check();
			} else if (ker.wVirtualKeyCode == VK_TAB || ker.wVirtualKeyCode == VK_DOWN) {
				if (item < amount) {
					items[item].unclick();
					isChecked[item] = 0;
					items[item + 1].click();
					isChecked[item + 1] = 1;
				}
			} else if (ker.wVirtualKeyCode == VK_UP) {
				if (item) return;
				items[whoClicked()].check();
			}
		}

	}
	
}

void CheckList::MouseEventProc(MOUSE_EVENT_RECORD mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Right button press
		if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED) {
			checkClickedPosition(mer.dwMousePosition);
			//if (isClicked == true) checked();
		}
		break;
	}
}
void CheckList::checkClickedPosition(COORD dwMousePosition) {
	CONSOLE_SCREEN_BUFFER_INFO ct;
	if (!GetConsoleScreenBufferInfo(handler, &ct))
	{
		cout << "GetConsoleScreenBufferInfo failed" << GetLastError << endl;
		return;
	}
	COORD c = ct.dwCursorPosition;
	if (c.X >= coord.X &&
		c.X <= (coord.X + width) &&
		c.Y >= coord.Y &&
		c.Y <= coord.Y + amount) {
		ifClicked = true;
	}
	else {
		ifClicked = false;
	}
}

int CheckList::whoClicked() {
	for (int i = 0; i < amount; i++) {
		if (isClicked[i]) return i;
	}
	return -1;
}
CheckList::~CheckList(){
}
