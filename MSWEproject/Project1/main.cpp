#include <Windows.h>
#include <stdio.h>
#include <string>
#include "Button.h"

using namespace std;

int main(VOID) {

	//non touchable cant react tp mouse and keyboard.
	//light green on a black background
	//located in someplace.
	//Label newLabel1 = Label(15, 10, "LABEL 1");
	//newLabel1.draw();
	IController *newController = new Button(20);
	((Button*)newController)->setText("Noam Star");
	newController->draw();
	getchar();
	return 0;
}