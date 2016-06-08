#pragma once
#include <Windows.h>
#include <string>
#include <iostream>
#include "../IController/IController.h"
using namespace std;

struct MouseListener
{
	virtual void MousePressed(IController &control, int x, int y, bool isLeft) = 0;
};

class Button : public IController
{
	string buttonStr;

public:

	Button(int width);
	~Button();

	void draw();
	bool handleInput(INPUT_RECORD);
	void setText(string value);
	void AddListener(MouseListener &listener);

};

