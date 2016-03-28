#pragma once
#include "RadioBox.h"
#include <vector>


using namespace std;


class RadioMaster
{
private:
	int size;
	SHORT firstY, lastY, currentY = 0;
	vector <RadioBox *> boxes;
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE in = GetStdHandle(STD_INPUT_HANDLE);

	CONSOLE_CURSOR_INFO noVisibleCursor;

	DWORD noBackground;
	DWORD backgroundOn;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


public:
	RadioMaster(string options[], int size);
	void setHoverBackgroundOn(int num);
	void setHoverBackgroundOff(int num);
	void addRadioBox(string option);
	void markRadio(int num);
	void setHoverBackground(SHORT y);
	void goUp();
	void goDown();
	void markHovered();

	~RadioMaster();
};

