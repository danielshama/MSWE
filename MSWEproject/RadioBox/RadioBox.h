#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef struct doubleCoord{
	COORD start;
	COORD end;
} doubleCoord;

class RadioBox
{
private:

	COORD checkPoint;
	doubleCoord optionCoords;
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
	~RadioBox();
};

