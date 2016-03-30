#pragma once
#include <Windows.h>
#include <stdio.h>

class TextBox {

private :

	HANDLE handle;
	char* textBoxBuf;
	COORD c;
	int maxSize, curserPosition;
	boolean isClicked;

	void createTextBox(int width);
	void keyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);

	void moveRight();
	void moveLeft();
	void deleteCharecter();
	void shiftLeft();
	void addCharecter(char c);
	void changeCurserPosition(int position);
	void checkClickedPosition(COORD dwMousePosition);

public:

	TextBox(int x, int y, int width);
	~TextBox();
	void handleInput(INPUT_RECORD iRecord);

};

