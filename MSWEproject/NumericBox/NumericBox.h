#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "../IController/IController.h"

class NumericBox : public IController
{
	int value;
	int max;
	int min;
	DWORD regularAttr;

public:
	NumericBox(int width, int min, int max);
	~NumericBox();

	int GetValue();
	bool SetValue(int value);

	//events handlers
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void checkClickedPosition(COORD dwMousePosition);
	void changeValue(int add);

	//Inharite
	void draw();
	void handleInput(INPUT_RECORD iRecord);
};

