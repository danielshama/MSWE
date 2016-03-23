#include "Label.h"
#include <iostream>

Label::Label()
{
}


Label::~Label()
{

}
 void Label::createLabel (int locationX, int locationY, string str) {

	 COORD c = { locationX, locationY };
	 HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	 SetConsoleCursorPosition(h, c);

	 //set cursor size and visibility example


	 //set foreground color

	 DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_GREEN | FOREGROUND_INTENSITY;
	 SetConsoleTextAttribute(h, wAttr);

	 cout << str;
	 cin >> str;

 }