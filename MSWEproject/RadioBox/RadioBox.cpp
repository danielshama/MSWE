#include "RadioBox.h"


RadioBox::RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn, HANDLE handle) {
	this->option = option;
	this->handle = handle;
	this->noBackground = noBackground;
	this->backgroundOn = backgroundOn;

	//makeRadioButton();

}


void RadioBox::makeRadioButton() {
	string s = "[ ] - " + option;
	
	SetConsoleTextAttribute(handle, noBackground);
	for (int i = 0; i < s.length() && i < loc.width; i++) {
		cout << s.at(i);
	}
	//GetConsoleScreenBufferInfo(out, &csbiInfo);
	//checkPoint = csbiInfo.dwCursorPosition;

	//cout << " ] - ";
	//GetConsoleScreenBufferInfo(out, &csbiInfo);
	//optionCoords.start = csbiInfo.dwCursorPosition;

	//cout << option;
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	//optionCoords.end = csbiInfo.dwCursorPosition;

	cout << endl;

}


BOOL RadioBox::isChecked() {
	return checked;
}

BOOL RadioBox::isHovered() {
	return hovered;
}

void RadioBox::setOnBackground() {
	DWORD background;
	for (int i = 0; i < loc.height; i++)
	if (!FillConsoleOutputAttribute(handle, backgroundOn, loc.width, { loc.x, loc.y }, &background)) {
			cout << "failed to change the background" << endl;
			exit(1);
		}
	hovered = TRUE;
}

void RadioBox::setOffBackground() {
	DWORD background;
	for (int i = 0; i < loc.height; i++)
	if (!FillConsoleOutputAttribute(handle, noBackground, loc.width, {loc.x, loc.y}, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	hovered = FALSE;
}

void RadioBox::markAsChecked() {
	SetConsoleCursorPosition(handle, { loc.x + 1, loc.y });
	cout << "X";
	setOnBackground();
	checked = TRUE;
}

void RadioBox::markAsUnchecked() {
	SetConsoleCursorPosition(handle, { loc.x + 1, loc.y });
	cout << " ";
	setOffBackground();
	checked = FALSE;
}

void RadioBox::setBoxLocation(short x, short y, int width, int height) {
	loc.x = x;
	loc.y = y;
	loc.width = width;
	loc.height = height;
}

SHORT RadioBox::getYAxis() {
	return loc.y;
}

RadioBox::~RadioBox()
{

}
