#include <Windows.h>
#include <stdio.h>
#include <string>
#include "Label.h"

using namespace std;

int main(VOID) {

	//non touchable cant react tp mouse and keyboard.
	//light green on a black background
	//located in someplace.
	//Label newLabel1 = Label(15, 10, "LABEL 1");
	//newLabel1.draw();
	IController *newLabel2 = new Label(30, 20, "LABEL 121212");
	newLabel2->draw();
	getchar();
	return 0;
}