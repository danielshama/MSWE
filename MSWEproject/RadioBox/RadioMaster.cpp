#include "RadioMaster.h"


RadioMaster::RadioMaster(int height, int width, vector<string> options) : 
	IController(width){

	loc.width = width;
	loc.height = height;
	//cout << endl;//going row down, just in case...
	itemOptions = options;
	size = (int)options.size();
}

void RadioMaster::draw() {
	//GetConsoleScreenBufferInfo(handle, &csbiInfo);
	SetConsoleCursorPosition(handle, { loc.x, loc.y });

	//firstY = csbiInfo.dwCursorPosition.Y;
	//noBackground = csbiInfo.wAttributes | BACKGROUND_BLUE;
	//backgroundOn = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;

	for (int i = 0; i < size; i++) {
		addRadioBox(itemOptions[i], i);
		SetConsoleCursorPosition(handle, { loc.x, (short)(loc.y + i+1) });
	}
	size = boxes.size();
	//GetConsoleScreenBufferInfo(handle, &csbiInfo);
	//lastY = csbiInfo.dwCursorPosition.Y - 1;

	noVisibleCursor = { 100, FALSE };
	SetConsoleCursorInfo(handle, &noVisibleCursor);
}

bool RadioMaster::handleInput(INPUT_RECORD ir)
{
	switch (ir.EventType)
	{
	case KEY_EVENT: // keyboard input 
		checkEventKey(ir);
		if (!isFocus) return false;
		//break;

	case MOUSE_EVENT: // mouse input 
		mouseEventProc(ir.Event.MouseEvent);
		if (!isFocus) return false;
		break;
	}
	return true;
}

bool RadioMaster::checkEventKey(INPUT_RECORD &irInBuf) {
	if (irInBuf.Event.KeyEvent.bKeyDown) {
		DWORD key = irInBuf.Event.KeyEvent.wVirtualKeyCode;
		if (key == VK_UP || key == VK_NUMPAD8) {
			goUp();
			return true;
		}
		if (key == VK_DOWN || key == VK_NUMPAD2) {
			goDown();
			return true;
		}
		if (key == VK_RETURN) {
			markHovered();
			return true;;
		}
		if (key == VK_TAB) {
			if (lastInList) {
				isFocus = false;
				return false;
			}
			goDown();
			return true;
		}
	}
}

void RadioMaster::mouseEventProc(MOUSE_EVENT_RECORD &mer) {
#ifndef MOUSE_HWHEELED
#define MOUSE_HWHEELED 0x0008
#endif

	if (!checkInLimits(mer)) return;
	switch (mer.dwEventFlags) {

	case 0:
		//Left button press
		if (mer.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED) {
			SHORT yPosition = mer.dwMousePosition.Y;
			if (yPosition >= loc.y && yPosition <= loc.y + loc.height - 1) {
				isFocus = true;
				setHoverBackground(yPosition);
				markHovered();
			}
			else {
				isFocus = false;
			}
			//checkClickedPosition(mer.dwMousePosition);
		}
		break;
	case MOUSE_MOVED:
		//Right button press

		SHORT yPosition = mer.dwMousePosition.Y;
		if (yPosition >= loc.y && yPosition <= loc.y + loc.height - 1) {
			setHoverBackground(yPosition);
		}
		break;
	}
}

void RadioMaster::addRadioBox(string option, int line) {
	RadioBox *temp = new RadioBox(option, dword, hoverBackground, handle);
	if (temp == NULL) {
		cout << "failed to create a RadioBox" << endl;
		exit(1);
	}
	
	temp->setBoxLocation(loc.x, loc.y + line, loc.width, 1);
	temp->makeRadioButton();
	boxes.push_back(temp);
}

void RadioMaster::markHovered() {
	SHORT needToMark = currentY - loc.y;
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
	lastInList = false;
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
	return loc.y;
}

SHORT RadioMaster::getBottomY() {
	return loc.y + loc.height - 1;
}

void RadioMaster::goUp() {
	if (currentY == loc.y) {//nowhere to go
		setHoverBackground(loc.y + loc.height - 1);
		return;
	}

	if (currentY == 0) {
		setHoverBackground(loc.y);
		return;
	}
	setHoverBackground(currentY - 1);
}

void RadioMaster::goDown() {
	short lastPosition = loc.y + loc.height - 1;
	if (currentY == lastPosition) {//nowhere to go
		setHoverBackground(loc.y);
		return;
	}
	/*
	if (currentY == 0) {
		setHoverBackground(loc.y + loc.height - 1);
		return;
	}*/
	setHoverBackground(currentY + 1);
	if (currentY == lastPosition) lastInList = true;
}


/*
boolean RadioMaster::checkInLimits(MOUSE_EVENT_RECORD &mer) {
	if (mer.dwMousePosition.X >= loc.x && mer.dwMousePosition.X <= loc.x + loc.width) {
		if (mer.dwMousePosition.Y >= loc.y && mer.dwMousePosition.Y <= loc.y + loc.height - 1)
			return true;
	}
	return false;
}*/



RadioMaster::~RadioMaster()
{
	int size = (int) boxes.size();
	for (int i = 0; i < size; i++) {
		free(boxes.at(i));
	}
	boxes.empty();
}

