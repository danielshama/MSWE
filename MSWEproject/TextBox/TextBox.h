#pragma once
#include <Windows.h>
#include <stdio.h>
#include "../IController/IController.h"

class TextBox : public IController {

private :

	char* textBoxBuf;
	int maxSize, curserPosition;
	bool keyEventProc(KEY_EVENT_RECORD ker);
	bool MouseEventProc(MOUSE_EVENT_RECORD mer);

	void moveRight();
	void moveLeft();
	void deleteCharecter();
	void shiftLeft();
	void addCharecter(char c);
	void changeCurserPosition(int position);
	void checkClickedPosition(COORD dwMousePosition);

public:

	TextBox(int width);
	TextBox(short x, short y, int width);
	~TextBox();
	void draw();
	bool handleInput(INPUT_RECORD iRecord);
};

