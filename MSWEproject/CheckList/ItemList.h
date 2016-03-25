#pragma once
#include <Windows.h>
#include <stdio.h>
#include <iostream>
#include "Label.h"


class ItemList
{
private:
	HANDLE handle;
	char* buffer;
	Label lbl;
	COORD coord;
	boolean isClicked;
public:
	ItemList(int x, int y, string str);
	void create();
	~ItemList();
};

