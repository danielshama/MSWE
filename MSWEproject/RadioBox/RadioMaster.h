#pragma once
#include "RadioBox.h"
#include <vector>
#include "../IController/IController.h"
#include <iostream>
using namespace std;


class RadioMaster : public IController
{
private:
	//HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	int size;
	SHORT firstY, lastY, currentY = 0;
	vector <RadioBox *> boxes;
	vector<string> itemOptions;

	CONSOLE_CURSOR_INFO noVisibleCursor;

	DWORD noBackground;
	DWORD backgroundOn;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


public:
	RadioMaster(vector<string> options);
	void draw();
	void handleInput(INPUT_RECORD ir);
	void addRadioBox(string option);
	void setHoverBackground(SHORT y);
	void goUp();
	void goDown();
	void markHovered();
	SHORT getTopY();
	SHORT getBottomY();
	void checkEvetnKey(INPUT_RECORD &irInBuf);
	void mouseEventProc(MOUSE_EVENT_RECORD &mer);

	~RadioMaster();
};

