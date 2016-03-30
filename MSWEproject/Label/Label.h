#pragma once

#include <Windows.h>
#include <string>
#include <iostream>

using namespace std;
class Label
{

private:
	HANDLE handle;
	COORD c;
	string labelStr;

public:
	Label(int x, int y, string str);
	Label(string str);
	~Label();
	void create();
	void create(COORD coord);
};

