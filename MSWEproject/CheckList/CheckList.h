#include <Windows.h>
#include <iostream>
#include "ItemList.h"
#include <vector>
using namespace std;

#pragma once
class CheckList
{
	private:
		int amount;
		COORD coord;
		string * options;
		int width;
		HANDLE handler;
		boolean ifClicked;
		vector<ItemList> items;
		vector<int> isChecked;
		vector<int> isClicked;
		boolean checkClickedPosition(COORD dwMousePosition);
		int whoClicked();
	public:
		CheckList(string opts[], int optAmount, short x, short y);
		void handleInput(INPUT_RECORD iRecord);
		void keyEventProc(KEY_EVENT_RECORD ker);
		void MouseEventProc(MOUSE_EVENT_RECORD mer);
		vector<int> whoChecked();

		~CheckList();
};

