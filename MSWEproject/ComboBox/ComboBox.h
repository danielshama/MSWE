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

	//the initial style
	void init();
	//combobox open/close
	void showOptions();
	void hideOptions();
	//events handlers
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void checkClickedPosition(COORD dwMousePosition);
	//the hover on choosen item and write it in the box
	void chooseOption(int top, int lastColoredLine);
	void setSelected(int listNum);
	//print the requested line
	void printDelimiter(int position);
	void printSpace(int position);
	void printOption(int position, int itemNum);

public:

	//ctor / dtor
	ComboBox(int x, int y, char* options[], int size);
	~ComboBox();
	//input handle
	void handleInput(INPUT_RECORD iRecord);

};

