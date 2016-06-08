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
	bool lastInList = false;

	CONSOLE_CURSOR_INFO noVisibleCursor;

	DWORD noBackground = csbiInfo.wAttributes | BACKGROUND_BLUE;
	DWORD backgroundOn = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;


public:
	RadioMaster(int height, int width, vector<string> options);
	void draw();
	bool handleInput(INPUT_RECORD ir);
	void addRadioBox(string option, int line);
	void setHoverBackground(SHORT y);
	void goUp();
	void goDown();
	void markHovered();
	SHORT getTopY();
	SHORT getBottomY();
	bool checkEventKey(INPUT_RECORD &irInBuf);
	void mouseEventProc(MOUSE_EVENT_RECORD &mer);

	~RadioMaster();
};

