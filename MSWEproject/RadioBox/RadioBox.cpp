#include "RadioBox.h"


RadioBox::RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn) {
	this->option = option;

	this->noBackground = noBackground;
	this->backgroundOn = backgroundOn;

	//makeRadioButton();

}


void RadioBox::makeRadioButton() {
	string s = "[ ] - " + option;

	for (int i = 0; i < s.length() && i < loc.width; i++) {
		cout << s.at(i);
	}
	//GetConsoleScreenBufferInfo(out, &csbiInfo);
	//checkPoint = csbiInfo.dwCursorPosition;

	//cout << " ] - ";
	//GetConsoleScreenBufferInfo(out, &csbiInfo);
	//optionCoords.start = csbiInfo.dwCursorPosition;

	//cout << option;
	GetConsoleScreenBufferInfo(out, &csbiInfo);
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
		if (!FillConsoleOutputAttribute(out, backgroundOn, loc.width - 6, { loc.x + 6, loc.y + i }, &background)) {
			cout << "failed to change the background" << endl;
			exit(1);
		}
	hovered = TRUE;
}

void RadioBox::setOffBackground() {
	DWORD background;
	for (int i = 0; i < loc.height; i++)
	if (!FillConsoleOutputAttribute(out, noBackground, loc.width - 6, {loc.x + 6, loc.y + i}, &background)) {
		cout << "failed to change the background" << endl;
		exit(1);
	}
	hovered = FALSE;
}

void RadioBox::markAsChecked() {
	SetConsoleCursorPosition(out, {loc.x + 1, loc.y});
	cout << "X";
	setOnBackground();
	checked = TRUE;
}

void RadioBox::markAsUnchecked() {
	SetConsoleCursorPosition(out, {loc.x + 1, loc.y});
	cout << " ";
	setOffBackground();
	checked = FALSE;
}

void RadioBox::setLocation(short x, short y, int width, int height) {
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
