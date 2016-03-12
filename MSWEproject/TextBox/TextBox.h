#pragma once
#include <Windows.h>
#include <stdio.h>

class TextBox {

private :

	HANDLE handle;
	char* textBoxBuf;
	COORD c;
	int maxSize;
	int curserPosition;
	boolean isClicked;

public:

	TextBox(int x, int y, int width);
	~TextBox();

	void createTextBox(int width);
	void handleInput(INPUT_RECORD iRecord);

	void keyEventProc(KEY_EVENT_RECORD ker);

	void moveRight();
	void moveLeft();
	void deleteCharecter();
	void addCharecter(char c);
	void changeCurserPosition(int position);
	void errorInput();
	void textBoxIsClicked(boolean clickInside);

};

