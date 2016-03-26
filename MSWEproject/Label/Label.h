#pragma once

#include <Windows.h>
#include <string>

using namespace std;
class Label
{

private:
	HANDLE handle;
	COORD c;
	string labelStr;

public:
	Label(int x, int y, string str);
	~Label();
	void createLabel();
};

