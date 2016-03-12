#include "TextBox.h"


TextBox::TextBox(int x, int y, int width) {

	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	c = { (short)x, (short)y };
	curserPosition = 0;
	textBoxBuf = new char[width];
	for (int i = 0; i < width; i++) {
		textBoxBuf[i] = ' ';
	}
	maxSize = width;
	isClicked = true;
	createTextBox(width);
}

void TextBox::createTextBox(int width) {

	SetConsoleCursorPosition(handle, c);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	SetConsoleTextAttribute(handle, wAttr2);
	for (int i = 0; i < width; i++) {
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
		//mouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		//errorInput();
		break;
	}
}

void TextBox::keyEventProc(KEY_EVENT_RECORD ker) {

	if (curserPosition >= 0  && curserPosition < maxSize) {
		if (ker.bKeyDown) {
			//RIGHT key pressed
			if (ker.wVirtualKeyCode == VK_RIGHT) {
				moveRight();
			}
			//LEFT key pressed
			else if (ker.wVirtualKeyCode == VK_LEFT) {
				moveLeft();
			}
			//BACKSPACE key pressed
			else if (ker.wVirtualKeyCode == VK_BACK) {
				deleteCharecter();
			}
			//Right mouse clicked
			else if (ker.wVirtualKeyCode == VK_RBUTTON) {
				
			} 
			//Write the charecter to the console 
			else addCharecter(ker.uChar.AsciiChar);
		}

	} else {
		curserPosition = (curserPosition < 0) ? 0 : maxSize-1;
	}
}


void TextBox::textBoxIsClicked(boolean clickInside) {
	isClicked = (clickInside) ? true : false;
	//if isClicked true ---> remove the curser from the textbox 
	//if isClicked false ---> add the curser to the curserPosition
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
}

void TextBox::addCharecter(char ch) {
	//set c (argument) where the curser stand 
	printf("%c", ch);
	textBoxBuf[curserPosition] = ch;
	moveRight();
}

void TextBox::changeCurserPosition(int position){
	COORD newCoord = { c.X + position, c.Y };
	SetConsoleCursorPosition(handle, newCoord);
}

void TextBox::errorInput() {
	printf("Unknown event type");
}

TextBox::~TextBox() {
	free(textBoxBuf);
}

