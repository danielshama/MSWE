#pragma once
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <string>
#include <vector>
#include "../IController/IController.h"

 
class Panel : public IController
{
private:
	vector<IController *> controllers;
	int foucosedIndex;

public:

	Panel(int height, int width);
	void addControl(IController *controller, short x, short y);
	bool handleInput(INPUT_RECORD ir);
	bool checkAvailableLocation(short x, short y, int width, int height);
	void draw();
	void MouseEventProc(INPUT_RECORD ir);
	bool keyEventProc(INPUT_RECORD ir);
	void foucosOnNextController();
	int getFocusIndex();
	~Panel();
};

