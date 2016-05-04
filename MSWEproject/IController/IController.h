#pragma once
#include <Windows.h>
using namespace std;

class IController {

protected:
	HANDLE handle;
	COORD c;
	int width;

public:
	IController(short x, short y, int width = 0) :
		c({ x,y }), width(width), handle(GetStdHandle(STD_OUTPUT_HANDLE)) {};
	virtual void draw() = 0 ;
	virtual void handleInput(INPUT_RECORD) = 0;
	~IController() {};
};

