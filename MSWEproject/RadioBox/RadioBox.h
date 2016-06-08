#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef struct boxLocation{
	short x, y;
	int width, height;
} boxLocation;

class RadioBox
{
private:

	//COORD checkPoint;
	boxLocation loc;
	string option;

	BOOL checked = FALSE;
	BOOL hovered = FALSE;

	DWORD noBackground;
	DWORD backgroundOn;

	HANDLE handle;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

public:
	RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn, HANDLE handle);

	void makeRadioButton();
	void setOnBackground();
	void setOffBackground();
	void markAsChecked();
	void markAsUnchecked();
	BOOL isChecked();
	BOOL isHovered();
	SHORT getYAxis();
	void setBoxLocation(short x, short y, int width, int height);
	~RadioBox();
};

