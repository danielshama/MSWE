#include "RadioBox.h"



RadioBox::RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn) {
	this -> option = option;

	this->noBackground = noBackground;
	this->backgroundOn = backgroundOn;

	makeRadioButton();

}

/*
RadioBox::RadioBox(int size, string options[])
{
	this->size = size;

	if (size <= 0) {
		cout << "There is no content to the RadioBox" << endl;
		exit(1);
	}



	cout << endl; //going down one line (just in case)

	places = new doubleCoord[size];

	radioPoints = new COORD[size];

	makeBoxes(options);

	noVisibleCursor = { 100, true };
	SetConsoleCursorInfo(out, &noVisibleCursor);
	SetConsoleCursorPosition(out, radioPoints[0]);
}
*/

/*
void RadioBox::makeBoxes(string options[]) {
	for (int i = 0; i < size; i++) {
		makeRadioButton(i, options[i]);
	}
}
*/

void RadioBox::makeRadioButton() {
	cout << "[";
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	checkPoint = csbiInfo.dwCursorPosition;

	cout << " ] - ";
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	optionCoords.start = csbiInfo.dwCursorPosition;

	cout << option;
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	optionCoords.end = csbiInfo.dwCursorPosition;

	cout << endl;

}

/*
void RadioBox::makeRadioButton(int num, string option) {
	cout << "(";
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	radioPoints[num].X = csbiInfo.dwCursorPosition.X;
	radioPoints[num].Y = csbiInfo.dwCursorPosition.Y;

	//noVisibleCursor = { 100, FALSE };
	//SetConsoleCursorInfo(out, &noVisibleCursor);
	cout << " ";

	//visibleCursor = { 50, TRUE };
	//SetConsoleCursorInfo(out, &visibleCursor);
	cout << ") - ";

	GetConsoleScreenBufferInfo(out, &csbiInfo);
	//I need the first coordinate of the option's sentence
	places[num].start.X = csbiInfo.dwCursorPosition.X;
	places[num].start.Y = csbiInfo.dwCursorPosition.Y;

	//Need to set the marking background - ask Kasus!!!

	//Putting the string (describes the option)
	cout << option;

	GetConsoleScreenBufferInfo(out, &csbiInfo);//saving the last coordinate of the radio option
	places[num].end.X = csbiInfo.dwCursorPosition.X;
	places[num].end.Y = csbiInfo.dwCursorPosition.Y;
	cout << endl;
}
*/

BOOL RadioBox::isChecked() {
	return checked;
}

BOOL RadioBox::isHovered() {
	return hovered;
}

void RadioBox::setOnBackground() {
	DWORD background;
	if (!FillConsoleOutputAttribute(out, backgroundOn, option.size(), optionCoords.start, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	hovered = TRUE;
}

void RadioBox::setOffBackground() {
	DWORD background;
	if (!FillConsoleOutputAttribute(out, noBackground, option.size(), optionCoords.start, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	hovered = FALSE;
}

void RadioBox::markAsChecked() {
	SetConsoleCursorPosition(out, checkPoint);
	cout << "X";
	setOnBackground();
	checked = TRUE;
}

void RadioBox::markAsUnchecked() {
	SetConsoleCursorPosition(out, checkPoint);
	cout << " ";
	setOffBackground();
	checked = FALSE;
}

SHORT RadioBox::getYAxis() {
	return checkPoint.Y;
}

RadioBox::~RadioBox()
{

}
