#pragma once
#include <Windows.h>
using namespace std;

class IController {

protected:
	HANDLE handle;
	COORD c;
	int width;

public:
	IController(short x, short y, int width = 0);
	~IController() {};
	virtual void draw() {};
};

