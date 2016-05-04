#include "CheckList.h"

CheckList::CheckList(string opts[], int optAmount, short x, short y):
	IController(x, y) {

	amount = optAmount;
	//coord = { x, y };
	ifClicked = true;
	options = opts;
	//handler = GetStdHandle(STD_OUTPUT_HANDLE);
	
	/*
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	width = 0;
	for (int i = 0; i < amount; i++) {
		if (width < opts[i].length()) width = opts[i].length();
		items.push_back(ItemList(x, y + i, opts[i]));
		items[i].create();
		isChecked.push_back(0);
		isClicked.push_back(0);
	}
	items[0].click();
	isClicked[0] = 1;
	*/
}

void CheckList::draw() {
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	width = 0;
	for (int i = 0; i < amount; i++) {
		if (width < options[i].length()) width = options[i].length();
		items.push_back(ItemList(c.X, c.Y + i, options[i]));
		items[i].create();
		isChecked.push_back(0);
		isClicked.push_back(0);
		items[0].click();
		isClicked[0] = 1;
	}
}

void CheckList::handleInput(INPUT_RECORD iRecord) {

	if (!ifClicked) return;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
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
	if (!GetConsoleScreenBufferInfo(handle, &ct))
	{
		cout << "GetConsoleScreenBufferInfo failed" << GetLastError << endl;
		return;
	}
	if (ker.bKeyDown) {
		int clickedItem = whoClicked();
		if (clickedItem < 0) return;
		//ENTER key pressed
		if (ker.wVirtualKeyCode == VK_RETURN) {
			items[clickedItem].check();
		}
		else if (ker.wVirtualKeyCode == VK_TAB || ker.wVirtualKeyCode == VK_DOWN || ker.wVirtualKeyCode == VK_NUMPAD2) {
			if (clickedItem < amount - 1) {
				items[clickedItem].unclick();
				isClicked[clickedItem] = 0;
				items[clickedItem + 1].click();
				isClicked[clickedItem + 1] = 1;
			}
		}
		else if (ker.wVirtualKeyCode == VK_UP || ker.wVirtualKeyCode == VK_NUMPAD8) {
			if (clickedItem > 0) {
				items[clickedItem].unclick();
				isClicked[clickedItem] = 0;
				items[clickedItem - 1].click();
				isClicked[clickedItem - 1] = 1;
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
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			if (checkMousePosition(mer.dwMousePosition)) {
				SHORT yPosition = mer.dwMousePosition.Y;
				items[yPosition - c.Y].check();
		}
	}
		break;
	case MOUSE_MOVED:
		if (checkMousePosition(mer.dwMousePosition)) {
			int clickedItem = whoClicked();
			if (clickedItem < 0) return;
			SHORT yPosition = mer.dwMousePosition.Y;
			items[clickedItem].unclick();
			isClicked[clickedItem] = 0;
			items[yPosition - c.Y].click();
			isClicked[yPosition - c.Y] = 1;
}
		break;
	}
}

boolean CheckList::checkMousePosition(COORD dwMousePosition) {
	if (dwMousePosition.X >= c.X &&
		dwMousePosition.X <= (c.X + width) &&
		dwMousePosition.Y >= c.Y &&
		dwMousePosition.Y <= c.Y + amount-1) {
		return true;
	}
	else {
		return false;
	}
}

int CheckList::whoClicked() {
	for (int i = 0; i < amount; i++) {
		if (isClicked[i]) return i;
	}
	return -1;
	}
vector<int>  CheckList::whoChecked() {
	return isChecked;
}
CheckList::~CheckList(){
}
