#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

typedef struct doubleCoord{
	COORD start;
	COORD end;
} doubleCoord;

class RadioBox
{
private:

	int size = 0;

	POINT *radioPoints;

	HANDLE *out;
	HANDLE *in;

	doubleCoord *places;

public:
	RadioBox(HANDLE *in, HANDLE *out, int size, string options[]);
	void makeBoxes(string options[]);
	void makeRadioButton(int num, string option);
	~RadioBox();
};

