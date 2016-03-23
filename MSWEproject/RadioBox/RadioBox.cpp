#include "RadioBox.h"



RadioBox::RadioBox(HANDLE *in, HANDLE *out, int size, string options[])
{
	this->size = size;

	if (size <= 0) {
		cout << "There is no content to the RadioBox" << endl;
		exit(1);
	}
	this->in = in;
	this->out = out;

	cout << endl; //going down one line (just in case)

	places = new doubleCoord[size];

	radioPoints = new POINT[size];

	makeBoxes(options);





	/*
	outHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	inHandle = GetStdHandle(STD_INPUT_HANDLE);

	COORD *coord = new COORD();
	coord->X = 0;
	coord->Y = 4;

	SetConsoleCursorPosition(outHandle, *coord);
	cout << "( )" << " The first radio option" << endl;
	cout << "( )" << " The second radio option" << endl;
	cout << "( )" << " The third radio option" << endl;
	*/
}

void RadioBox::makeBoxes(string options[]) {
	for (int i = 0; i < size; i++) {
		makeRadioButton(i, options[i]);
	}
}

void RadioBox::makeRadioButton(int num, string option) {
	POINT *tempPoint = new POINT();
	cout << "(";
	GetCursorPos(tempPoint);
	radioPoints[num].x = tempPoint->x;
	radioPoints[num].y = tempPoint->y;
	cout << " ) - ";

	GetCursorPos(tempPoint);
	//I need the first coordinate of the option's sentence
	places[num].start.X = (int)tempPoint->x;
	places[num].start.Y = (int)tempPoint->y;

	//Need to set the marking background - ask Kasus!!!

	//Putting the string (describes the option)
	cout << option;

	GetCursorPos(tempPoint);//saving the last coordinate of the radio option
	places[num].end.X = (int)tempPoint->x;
	places[num].end.Y = (int)tempPoint->y;
	cout << endl;


}

RadioBox::~RadioBox()
{

}
