#include "CheckList.h"

CheckList::CheckList(string opts[], int optAmount){
	amount = optAmount;
	options = opts;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
}

CheckList::CheckList(string opts[], int optAmount, COORD crd){
	amount = optAmount;
	coord = crd;
	options = opts;
	h = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci = { 70, FALSE };
	SetConsoleCursorInfo(h, &cci);
}
void CheckList::display() {
	SetConsoleCursorPosition(h, coord);
	DWORD wAttr = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY;
	SetConsoleTextAttribute(h, wAttr);
	printf("Check List:\n");
	for (int i = 0; i < amount; i++) {
		printf("\xDA\xBF\n\xC0\xD9 %s", options[i]);
	}
	
}

CheckList::~CheckList(){
}
