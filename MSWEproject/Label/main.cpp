#include <Windows.h>
#include <stdio.h>
#include <string>
#include "Label.h"

using namespace std;

int main(void) {

	//non touchable cant react tp mouse and keyboard.
	//light green on a black background
	//located in someplace.
	Label newLabel = Label(30, 10, "Mor Kasus label:");
	newLabel.create();
	getchar();
	return 0;
}