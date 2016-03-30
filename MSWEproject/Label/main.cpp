#include <Windows.h>
#include <stdio.h>
#include <string>
#include "Label.h"

using namespace std;

int main(VOID) {

	//non touchable cant react tp mouse and keyboard.
	//light green on a black background
	//located in someplace.
	Label newLabel1 = Label(15, 10, "LABEL 1");
	newLabel1.create();
	Label newLabel2 = Label(30, 20, "LABEL 2");
	newLabel2.create();
	getchar();
	return 0;
}