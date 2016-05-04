#pragma once

#include <Windows.h>
#include <string>
#include <iostream>
#include "../IController/IController.h"

using namespace std;
class Label : public IController{

private:
	string labelStr;
public:
	Label(short x, short y, string str);
	~Label() {};
	void draw();
	void handleInput(INPUT_RECORD) {};
};

