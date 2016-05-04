#include "TextBox.h"


TextBox::TextBox(int x, int y, int width) {

	int i;
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	c = { (short)x, (short)y };
	curserPosition = 0;
	textBoxBuf = new char[width];
	for (i = 0; i < width; i++) {
		textBoxBuf[i] = ' ';
	}
	maxSize = width;
	isClicked = true;
	createTextBox(width);
}

void TextBox::createTextBox(int width) {

	int i;
	SetConsoleCursorPosition(handle, c);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr = BACKGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttr);
	for (i = 0; i < width; i++) {
		printf("%c", textBoxBuf[i]);
	}
}

void TextBox::handleInput(INPUT_RECORD iRecord) {

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	changeCurserPosition(curserPosition);
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

void TextBox::keyEventProc(KEY_EVENT_RECORD ker) {

	if (!isClicked) return;
	if (ker.bKeyDown) {
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
			if (curserPosition < maxSize - 3) {
				moveRight();
				moveRight();
				moveRight();
			}
		}
		//Write the charecter to the console 
		else addCharecter(ker.uChar.AsciiChar);
	}
}

void TextBox::MouseEventProc(MOUSE_EVENT_RECORD mer) {
	#ifndef MOUSE_HWHEELED
	#define MOUSE_HWHEELED 0x0008
	#endif
	switch (mer.dwEventFlags) {
		
		case 0:
			//Right button press
			if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
				checkClickedPosition(mer.dwMousePosition);
			}
			break;
	}
}

void TextBox::checkClickedPosition(COORD dwMousePosition) {
	CONSOLE_CURSOR_INFO cci;
	if (dwMousePosition.Y == c.Y && ((dwMousePosition.X >= c.X) && (dwMousePosition.X < c.X + maxSize))) {
		isClicked = true;
		cci = { 10, TRUE };
		SetConsoleCursorInfo(handle, &cci);
		curserPosition = dwMousePosition.X - c.X;
		changeCurserPosition(curserPosition);
	}
	else {
		cci = { 100, FALSE };
		SetConsoleCursorInfo(handle, &cci);
		isClicked = false;
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
	COORD newCoord = { (short) c.X + (short) position, c.Y };
	SetConsoleCursorPosition(handle, newCoord);
}


TextBox::~TextBox() {
	free(textBoxBuf);
}

