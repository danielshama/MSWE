#pragma once


#include <Windows.h>
#include <string>
using namespace std;
class Label
{

	

public:
	Label();
	~Label();
	int locationY;
	int hlocationX;
	string str;
	void createLabel(int locationX, int locationY, string str);
};

