#include "TextBox.h"


TextBox::TextBox(int width) :
	IController(width) {
	loc.height = 1;
	isFocusable = true;
	int i;
	curserPosition = 0;
	textBoxBuf = new char[width];
	for (i = 0; i < width; i++) {
		textBoxBuf[i] = ' ';
	}
	maxSize = width;
	wAttr = BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
}

void TextBox::draw() {

	int i;
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	SetConsoleTextAttribute(handle, wAttr);
	for (i = 0; i < maxSize; i++) {
		printf("%c", textBoxBuf[i]);
	}
}

bool TextBox::handleInput(INPUT_RECORD iRecord) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	changeCurserPosition(curserPosition);
	bool res = true;
	switch (iRecord.EventType)
	{
	case KEY_EVENT: // keyboard input 
		res = keyEventProc(iRecord.Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input 
		res = MouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		break;
	}
	return res;
}

bool TextBox::keyEventProc(KEY_EVENT_RECORD ker) {

	bool res = true;
	if (!isFocus) return false;
	if (ker.bKeyDown) {
		SetConsoleTextAttribute(handle, wAttr);
		//RIGHT key pressed
		if (ker.wVirtualKeyCode == VK_RIGHT) {
			moveRight();
		}
		//LEFT key pressed
		else if (ker.wVirtualKeyCode == VK_LEFT) {
			moveLeft();
		}
		//RIGHT key pressed
		else if (ker.wVirtualKeyCode == VK_RWIN) {
			moveRight();
		}
		//LEFT key pressed
		else if (ker.wVirtualKeyCode == VK_LWIN) {
			moveLeft();
		}
		//BACKSPACE key pressed
		else if (ker.wVirtualKeyCode == VK_BACK) {
			deleteCharecter();
		}
		//TAB key pressed
		else if (ker.wVirtualKeyCode == VK_TAB) {
			isFocus = false;
			res = false;
			CONSOLE_CURSOR_INFO cci;
			cci = { 100, FALSE };
			SetConsoleCursorInfo(handle, &cci);
		}
		//Write the charecter to the console 
		else addCharecter(ker.uChar.AsciiChar);
	}
	return res;
}

bool TextBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
	#ifndef MOUSE_HWHEELED
	#define MOUSE_HWHEELED 0x0008
	#endif
	bool res = true;
	switch (mer.dwEventFlags) {
		case 0:
			//Right button press
			if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				checkClickedPosition(mer.dwMousePosition);
				if (!isFocus) {
					res = false;
				}
			}
			break;
	}
	return res;
}

void TextBox::checkClickedPosition(COORD dwMousePosition) {
	CONSOLE_CURSOR_INFO cci;
	if (dwMousePosition.Y == loc.y && ((dwMousePosition.X >= loc.x) && (dwMousePosition.X < loc.x + maxSize))) {
		isFocus = true;
		cci = { 10, TRUE };
		SetConsoleCursorInfo(handle, &cci);
		curserPosition = dwMousePosition.X - loc.x;
		changeCurserPosition(curserPosition);
	}
	else {
		cci = { 100, FALSE };
		SetConsoleCursorInfo(handle, &cci);
		isFocus = false;
	}
}

void TextBox::moveRight() {
	//set the curser one place right
	if (curserPosition >= maxSize-1) return;
	curserPosition++;
	changeCurserPosition(curserPosition);
}

void TextBox::moveLeft() {
	//set the curser one place left
	if (curserPosition <= 0) return;
	curserPosition--;
	changeCurserPosition(curserPosition);
}

void TextBox::deleteCharecter(){
	//set space where the curser stand 
	printf(" ");
	textBoxBuf[curserPosition] = ' ';
	moveLeft();
	shiftLeft();
}

void TextBox::shiftLeft() {
	int curserPtr = curserPosition, i;
	moveRight();
	for (i = curserPtr + 1; i < maxSize-1; i++) {
		textBoxBuf[i] = textBoxBuf[i + 1];
		addCharecter(textBoxBuf[i]);
	}
	textBoxBuf[maxSize - 1] = ' ';
	addCharecter(textBoxBuf[maxSize - 1]);
	curserPosition = curserPtr;
	changeCurserPosition(curserPtr);
}

void TextBox::addCharecter(char ch) {
	//set c (argument) where the curser stand 
	printf("%c", ch);
	textBoxBuf[curserPosition] = ch;
	moveRight();
}

void TextBox::changeCurserPosition(int position){
	COORD newCoord = { (short) loc.x + (short) position, loc.y };
	SetConsoleCursorPosition(handle, newCoord);
}


TextBox::~TextBox() {
	free(textBoxBuf);
}

