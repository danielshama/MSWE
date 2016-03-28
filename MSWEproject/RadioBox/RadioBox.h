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

	//int size = 0;

	//COORD *radioPoints;

	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	//doubleCoord *places;

	//CONSOLE_CURSOR_INFO noVisibleCursor;
	//CONSOLE_CURSOR_INFO visibleCursor;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;

public:
	RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn);
	//RadioBox(int size, string options[]);
	//void makeBoxes(string options[]);

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

