#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "../IController/IController.h"
using namespace std;

class Button : public IController
{
	string buttonStr;

public:

	Button(int width);
	~Button();

	void draw();
	void handleInput(INPUT_RECORD) {};
	void setText(string value);
};

