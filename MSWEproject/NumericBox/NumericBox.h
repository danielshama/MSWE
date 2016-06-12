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

public:
	NumericBox(int width, int min, int max);
	~NumericBox();

	int GetValue();
	bool SetValue(int value);

	void setMin(int min);
	void setMax(int max);

	//events handlers
	void MouseEventProc(MOUSE_EVENT_RECORD mer);
	void keyEventProc(KEY_EVENT_RECORD ker);
	void checkClickedPosition(COORD dwMousePosition);
	void changeValue(int add);

	//Inharite
	void draw();
	bool handleInput(INPUT_RECORD iRecord);
};

