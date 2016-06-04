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

	Label(int width);
	~Label() {};
	void draw();
	bool handleInput(INPUT_RECORD) { return false; };
	void setText(string value);

};

