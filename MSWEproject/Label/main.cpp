#include <Windows.h>
#include <stdio.h>
#include <string>
#include "Label.h"

using namespace std;

int main(VOID) {

	//non touchable cant react tp mouse and keyboard.
	//light green on a black background
	//located in someplace.
	
	Label *a = new Label();
	a->createLabel(30, 10, "Mor Kasus label:");

	
	
	/*
	COORD c = { 7, 7 };
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleCursorPosition(h, c);

	//set cursor size and visibility example

	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(h, &cci);

	//set foreground color

	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);

	printf("hello yellow ? world\n");

	CONSOLE_SCREEN_BUFFER_INFO cbi;

	GetConsoleScreenBufferInfo(h, &cbi);

	DWORD wAttr2 = cbi.wAttributes | BACKGROUND_BLUE | BACKGROUND_GREEN;
	SetConsoleTextAttribute(h, wAttr2);

	printf("ugly background yellow foreground\n");

	GetConsoleScreenBufferInfo(h, &cbi);

	DWORD a = cbi.wAttributes &  ~(BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY);
	SetConsoleTextAttribute(h, a);


	//what color will that print ?
	printf("hello  ??? world\n");

	GetConsoleScreenBufferInfo(h, &cbi);
	a = cbi.wAttributes | COMMON_LVB_REVERSE_VIDEO;
	SetConsoleTextAttribute(h, a);

	printf("and now ?");

	getchar();
	*/
	return 0;
}