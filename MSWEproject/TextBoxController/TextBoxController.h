#pragma once

#ifdef MATHFUNCSDLL_EXPORTS
#define MATHFUNCSDLL_API __declspec(dllexport) 
#else
#define MATHFUNCSDLL_API __declspec(dllimport) 
#endif

#include <Windows.h>
#include <stdio.h>
#include "../IController/IController.h"

class TextBoxController : public IController {

private:

	char* textBoxBuf;
	int maxSize, curserPosition;
	boolean isClicked;

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

	TextBox(short x, short y, int width);
	~TextBox();
	void draw();
	void handleInput(INPUT_RECORD iRecord);

};



