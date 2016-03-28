#include "RadioBox.h"


RadioBox::RadioBox(string option, DWORD &noBackground, DWORD &backgroundOn) {
	this->option = option;

	this->noBackground = noBackground;
	this->backgroundOn = backgroundOn;

	makeRadioButton();

}


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
