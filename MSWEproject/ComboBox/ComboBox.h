#pragma once
#include <Windows.h>
#include <stdio.h>

class ComboBox
{

private:

	HANDLE handle;
	COORD c;
	char* choosen;
	int listSize;
	int width;
	char** list;
	boolean isOpen;
	DWORD regularAttr;


	void init(); 
	void showOptions();
	void hideOptions();
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void checkClickedPosition(COORD dwMousePosition);

	void chooseOption(int top);
	void printDelimiter(int top);
	void printSpace(int top);
	void printOption(int top, int itemNum);

public:

	ComboBox(int x, int y, char* options[], int size);
	~ComboBox();
	void handleInput(INPUT_RECORD iRecord);

};

