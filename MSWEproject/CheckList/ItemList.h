#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
//#include "Label.h"
using namespace std;


class ItemList
{
private:
	HANDLE handle;
	char* buffer;
	string lbl;
	COORD coord;
	boolean isClicked;
	boolean isChecked;
	int curserPosition;
	short size;

public:
	ItemList(int x, int y, string str);
	void create();
	void check();
	void click();
	void unclick();
	~ItemList();
};

