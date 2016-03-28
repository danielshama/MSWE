#include "RadioMaster.h"



RadioMaster::RadioMaster(string options[], int size)
{
	if (size < 2) {
		cout << "not enough options" << endl;
		exit(1);
	}

	cout << endl;//going row down, just in case...

	GetConsoleScreenBufferInfo(out, &csbiInfo);

	firstY = csbiInfo.dwCursorPosition.Y;
	noBackground = csbiInfo.wAttributes;
	backgroundOn = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	for (int i = 0; i < size; i++) {
		addRadioBox(options[i]);
	}
	this->size = boxes.size();
	GetConsoleScreenBufferInfo(out, &csbiInfo);
	lastY = csbiInfo.dwCursorPosition.Y - 1;

	noVisibleCursor = { 100, FALSE };
	SetConsoleCursorInfo(out, &noVisibleCursor);

}



void RadioMaster::addRadioBox(string option) {
	RadioBox *temp = new RadioBox(option, noBackground, backgroundOn);
	if (temp == NULL) {
		cout << "failed to create a RadioBox" << endl;
		exit(1);
	}
	boxes.push_back(temp);

}

void RadioMaster::markRadio(int num) {
	RadioBox *temp = boxes.at(num);
	if (!temp->isChecked()) {
		temp->markAsChecked();
	}
}

void RadioMaster::markHovered() {
	SHORT needToMark = currentY - firstY;
	for (int i = 0; i < size; i++) {
		RadioBox *temp = boxes.at(i); 
		if (i == needToMark) {
			temp->markAsChecked();
			continue;
		}
		temp->markAsUnchecked();
	}
}

void RadioMaster::setHoverBackground(SHORT y) {
	for (int i = 0; i < size; i++) {
		RadioBox *temp = boxes.at(i);
		SHORT radioY = temp->getYAxis();
		if (radioY == y) {
			if (!temp->isHovered() && !temp->isChecked() ) {
				temp->setOnBackground();
				currentY = y;
			}
		} else {
			if (!temp->isChecked() && temp->isHovered()) {
				temp->setOffBackground();
			}
		}
	}
}

void RadioMaster::goUp() {
	if (currentY == firstY) return;//nowhere to go
	if (currentY == 0) {
		setHoverBackground(firstY);
		return;
	}
	setHoverBackground(currentY - 1);
}

void RadioMaster::goDown() {
	if (currentY == lastY) return;//nowhere to go
	if (currentY == 0) {
		setHoverBackground(lastY);
		return;
	}
	setHoverBackground(currentY + 1);
}

RadioMaster::~RadioMaster()
{
	int size = boxes.size();
	for (int i = 0; i < size; i++) {
		free(boxes.at(i));
	}
	boxes.empty();
}

