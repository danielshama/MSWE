#pragma once
#include <Windows.h>
#include <stdio.h>

class TextBox {

private :

	char textBoxBuf[50];
	COORD c;
	int amount;
	int maxSize;
	int cruserPosition;


public:

	TextBox(int x, int y, int width, int size);
	~TextBox();

	void createTextBox(int width);
	void handleInput(INPUT_RECORD iRecord);

	void keyEventProc(KEY_EVENT_RECORD ker);
	void mouseEventProc(MOUSE_EVENT_RECORD mer);

	void moveRight();
	void moveLeft();
	void deleteCharecter();
	void addCharecter(char c);
	void errorInput();
	boolean textBoxIsClicked(COORD c);

};

