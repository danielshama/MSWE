#include "RadioMaster.h"


RadioMaster::RadioMaster(vector<string> options) : 
	IController(0,0){
	size = (int) options.size();
	if (size < 2) {
		cout << "not enough options" << endl;
		exit(1);
	}
	cout << endl;//going row down, just in case...
	itemOptions = options;
}

void RadioMaster::draw() {
	GetConsoleScreenBufferInfo(handle, &csbiInfo);

	firstY = csbiInfo.dwCursorPosition.Y;
	noBackground = csbiInfo.wAttributes;
	backgroundOn = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	for (int i = 0; i < size; i++) {
		addRadioBox(itemOptions[i]);
	}
	this->size = boxes.size();
	GetConsoleScreenBufferInfo(handle, &csbiInfo);
	lastY = csbiInfo.dwCursorPosition.Y - 1;

	noVisibleCursor = { 100, FALSE };
	SetConsoleCursorInfo(handle, &noVisibleCursor);
}

void RadioMaster::handleInput(INPUT_RECORD ir)
{
	switch (ir.EventType)
	{
	case KEY_EVENT: // keyboard input 
		checkEvetnKey(ir);
		break;

	case MOUSE_EVENT: // mouse input 
		mouseEventProc(ir.Event.MouseEvent);
		break;
	}
}

void RadioMaster::addRadioBox(string option) {
	RadioBox *temp = new RadioBox(option, noBackground, backgroundOn);
	if (temp == NULL) {
		cout << "failed to create a RadioBox" << endl;
		exit(1);
	}
	boxes.push_back(temp);
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
			if (!temp->isHovered() && !temp->isChecked()) {
				temp->setOnBackground();
				
			}
			currentY = y;
		}
		else {
			if (!temp->isChecked() && temp->isHovered()) {
				temp->setOffBackground();
			}
		}
	}
}

SHORT RadioMaster::getTopY() {
	return firstY;
}

SHORT RadioMaster::getBottomY() {
	return lastY;
}

void RadioMaster::goUp() {
	if (currentY == firstY) {//nowhere to go
		setHoverBackground(lastY);
		return;
	}
	if (currentY == 0) {
		setHoverBackground(firstY);
		return;
	}
	setHoverBackground(currentY - 1);
}

void RadioMaster::goDown() {
	if (currentY == lastY) {//nowhere to go
		setHoverBackground(firstY);
		return;
	}
	if (currentY == 0) {
		setHoverBackground(lastY);
		return;
	}
	setHoverBackground(currentY + 1);
}

void RadioMaster::checkEvetnKey(INPUT_RECORD &irInBuf) {
	if (irInBuf.Event.KeyEvent.bKeyDown) {
		DWORD key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		if (key == VK_UP || key == VK_NUMPAD8) {
			goUp();
		}
		if (key == VK_DOWN || key == VK_TAB || key == VK_NUMPAD2) {
			goDown();
		}
		if (key == VK_RETURN) {
			markHovered();
		}	
	}
}

void RadioMaster::mouseEventProc(MOUSE_EVENT_RECORD &mer) {
	#ifndef MOUSE_HWHEELED
	#define MOUSE_HWHEELED 0x0008
	#endif
	switch (mer.dwEventFlags) {

	case 0:
		//Left button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			SHORT yPosition = mer.dwMousePosition.Y;
			if (yPosition >= firstY && yPosition <= lastY) {
				setHoverBackground(yPosition);
				markHovered();
			}
			//checkClickedPosition(mer.dwMousePosition);
		}
		break;
	case MOUSE_MOVED:
		//Right button press

		SHORT yPosition = mer.dwMousePosition.Y;
		if (yPosition >= firstY && yPosition <= lastY) {
			setHoverBackground(yPosition);
		}
		break;
	}
}

RadioMaster::~RadioMaster()
{
	int size = (int) boxes.size();
	for (int i = 0; i < size; i++) {
		free(boxes.at(i));
	}
	boxes.empty();
}

