#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "../IController/IController.h"

class ComboBox : public IController
{

private:

	string choosen;
	vector<string> list;
	int listSize, width;
	bool isOpen;
	int listItemOn;

	//the initial style
	void draw();
	//combobox open/close
	void showOptions();
	void hideOptions();

	//events handlers
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void keyEventProc(KEY_EVENT_RECORD ker);
	void checkClickedPosition(COORD dwMousePosition);

	//the hover on choosen item and write it in the box
	void chooseOption(int top, int lastColoredLine);
	void setHover(COORD dwMousePosition);
	void checkKey(int listItem);

	//print the requested line
	void printDelimiter(int position);
	void printSpace(int position);
	void printOption(int position, int itemNum);
	void printChoosen();
	void printOptionHoverd(int position, int lastBackgroundLine);

public:

	//ctor / dtor
	ComboBox(int width, vector<string> entries);
	ComboBox(int x, int y, char* options[], int size);
	~ComboBox();
	//input handle
	bool handleInput(INPUT_RECORD iRecord);

	//index selection
	size_t GetSelectedIndex();
	void SetSelectedIndex(size_t listNum);


};