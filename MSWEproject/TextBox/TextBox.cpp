#include "TextBox.h"


TextBox::TextBox(int x, int y, int width, int size) {

	c = { x, y };
	cruserPosition = 0;
	maxSize = size;
	amount = maxSize;

	createTextBox(width);
}

void TextBox::createTextBox(int width) {

	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(h, c);

	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(h, &cbi);
	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	SetConsoleTextAttribute(h, wAttr2);

	for (int i = 0; i < width; i++) {
		printf(" ");
	}
}

void TextBox::handleInput(INPUT_RECORD iRecord) {

	switch (iRecord.EventType)
	{
	case KEY_EVENT: // keyboard input 
		keyEventProc(iRecord.Event.KeyEvent);
		break;

	case MOUSE_EVENT: // mouse input 
		mouseEventProc(iRecord.Event.MouseEvent);
		break;

	default:
		errorInput();
		break;
	}
}

void TextBox::keyEventProc(KEY_EVENT_RECORD ker)
{
}

void TextBox::mouseEventProc(MOUSE_EVENT_RECORD mer){
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif
	printf("Mouse event: ");

	switch (mer.dwEventFlags)
	{
	case 0:

		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			printf("left button press \n");
		}
		else if (mer.dwButtonState == RIGHTMOST_BUTTON_PRESSED)
		{
			printf("right button press \n");
		}
		else
		{
			printf("button press\n");
		}
		break;
	case DOUBLE_CLICK:
		printf("double click\n");
		break;
	case MOUSE_HWHEELED:
		printf("horizontal mouse wheel\n");
		break;
	case MOUSE_MOVED:
		printf("mouse moved\n");
		break;
	case MOUSE_WHEELED:
		printf("vertical mouse wheel\n");
		break;
	default:
		printf("unknown\n");
		break;
	}
}

boolean TextBox::textBoxIsClicked(COORD c)
{

	return true;
}

void TextBox::moveRight()
{
}

void TextBox::moveLeft()
{
}

void TextBox::deleteCharecter()
{
}

void TextBox::addCharecter(char c)
{
}

void TextBox::errorInput() {
	printf("Unknown event type");
}

TextBox::~TextBox() {

}

