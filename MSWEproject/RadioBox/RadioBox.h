#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef struct{
	short x, y;
	int width, height;
} Location;

class RadioBox
{
private:

	//COORD checkPoint;
	Location loc;
	string option;

	BOOL checked = FALSE;
	BOOL hovered = FALSE;

	DWORD noBackground;
	DWORD backgroundOn;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

public:
	RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn);

	void makeRadioButton();
	void setOnBackground();
	void setOffBackground();
	void markAsChecked();
	void markAsUnchecked();
	BOOL isChecked();
	BOOL isHovered();
	SHORT getYAxis();
	void setLocation(short x, short y, int width, int height);
	~RadioBox();
};

