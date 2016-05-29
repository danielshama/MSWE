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
	IController *newLabel2 = new Label(40);
	((Label*)newLabel2)->setText("Noam Star the gaylord master of the Knight watch");
	newLabel2->draw();
	getchar();
	return 0;
}