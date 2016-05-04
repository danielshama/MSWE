#include <Windows.h>
#include <iostream>
#include "ItemList.h"
#include <vector>
#include "../IController/IController.h"
using namespace std;

#pragma once
class CheckList : public IController
{
private:
	int amount;
	//COORD c;
	string * options;
	int width;
	//HANDLE handle;
	boolean ifClicked;
	vector<ItemList> items;
	vector<int> isChecked;
	vector<int> isClicked;
	boolean checkMousePosition(COORD dwMousePosition);
	int whoClicked();
public:
	CheckList(string opts[], int optAmount, short x, short y);
	void handleInput(INPUT_RECORD iRecord);
	void keyEventProc(KEY_EVENT_RECORD ker);
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void draw();
	vector<int> whoChecked();

	~CheckList();
};
