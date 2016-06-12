#include "Panel.h"

Panel::Panel(int height, int width) : IController(width)
{
	loc.height = height;
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	foucosedIndex = -1;
}

bool Panel::handleInput(INPUT_RECORD ir) {
	handle = GetStdHandle(STD_OUTPUT_HANDLE);
	switch (ir.EventType)
	{
	case MOUSE_EVENT: // mouse input
		if(!MouseEventProc(ir)) return false;
		break;

	case KEY_EVENT: // keyboard input 
		if (!keyEventProc(ir)) {
			foucosOnNextController();
		}
		break;
	default:
		break;
	}
	return true;
}

bool Panel::MouseEventProc(INPUT_RECORD ir) {
	MOUSE_EVENT_RECORD mer = ir.Event.MouseEvent;
	if (!checkClickInPanel(mer)) return false;
	for (int i = 0; i < controllers.size(); i++) controllers[i]->handleInput(ir);
	return true;
}


bool Panel::keyEventProc(INPUT_RECORD ir) {
	bool res = true;
	if (foucosedIndex == -1) return false;
	else {
		res = controllers[getFocusIndex()]->handleInput(ir);
	}
	return res;
}

Panel::~Panel()
{
}

bool Panel::checkClickInPanel(MOUSE_EVENT_RECORD mer) {
	if (mer.dwMousePosition.Y > loc.y - 1 && mer.dwMousePosition.Y < loc.y + loc.height + 1 
		&& mer.dwMousePosition.X > loc.x - 1 && mer.dwMousePosition.X < loc.x + loc.width + 1) {
		isFocus = true;
	}
	else {
		isFocus = false;
	}
	return isFocus;
}

void Panel::addControl(IController *controller, short x, short y) {
	controller->setLocation(loc.x + x, loc.y + y);
	Location locTemp = controller->getLocation();
	if (checkAvailableLocation(locTemp.x, locTemp.y, locTemp.width, locTemp.height)) {
		if (!controlFocused){
			if (controller->getIsFocusable()) {
				controller->isFocus = true;
				controlFocused = true;
				foucosedIndex = controllers.size();
			}
		}
		controllers.push_back(controller);
	}
}

bool Panel::checkAvailableLocation(short x, short y, int width, int height) {
	Location controllerLoc(x, y, width, height);
	Location actualLoc = loc;
	actualLoc.x++;
	actualLoc.y++;
	actualLoc.height-=2;
	actualLoc.width-=2;
	//first we check if it's in the panel area
	if ((controllerLoc.x + controllerLoc.width) > (actualLoc.x + actualLoc.width) ||
		(controllerLoc.y + controllerLoc.height) > (actualLoc.y + actualLoc.height)) return false;
	size_t vecSize = controllers.size();
	//now we check if the location is not taken by another controller in the panel
	for (int i = 0; i < vecSize; i++) {
		Location existLoc = controllers[i]->getLocation();
		//now we need to check if there is any collision between the controllers in the panel
		if ((controllerLoc.x + controllerLoc.width) < existLoc.x ||
			(existLoc.x + existLoc.width) < controllerLoc.x) {
			continue;
		}
		else if ((controllerLoc.y + controllerLoc.height) > actualLoc.y ||
			(existLoc.y + existLoc.height) < controllerLoc.y) {
			continue;
		}
		return false;
	}
	return true;
}

void Panel::draw() {
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	DWORD wAttr = BACKGROUND_INTENSITY;
	SetConsoleTextAttribute(handle, wAttr);
	string frameLength;
	for (int i = 0; i <= loc.width; i++) frameLength += " ";
	cout << frameLength;
	for (short i = 1; i < loc.height; i++) {
		SetConsoleCursorPosition(handle, { loc.x, loc.y + i });
		cout << " ";
		SetConsoleCursorPosition(handle, { loc.x + (short)loc.width, loc.y + i });
		cout << " ";
		SetConsoleTextAttribute(handle, dword);
		for (short j = 1; j < loc.width; j++) {
			SetConsoleCursorPosition(handle, { loc.x + j, short(loc.y + i)});
			cout << " ";
		}
		SetConsoleTextAttribute(handle, wAttr);
	}

	SetConsoleCursorPosition(handle, { loc.x, loc.y + (short)loc.height });
	cout << frameLength;
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	SetConsoleTextAttribute(handle, defaulteDword);
	for (int i = 0; i < controllers.size(); i++) {
		controllers[i]->draw();
	}
}

void Panel::foucosOnNextController() {
	int index = foucosedIndex;
	while (1) {
		index++;
		if (controllers.size() == index) index = 0;
		if (controllers[index]->isFocusable){
			controllers[index]->isFocus = true;
			break;
		}
	}
}

int Panel::getFocusIndex() {
	int res = 0;
	for (int i=0; i < controllers.size(); i++) {
		if (controllers[i]->isFocus) {
			res = i;
			foucosedIndex = i;
			break;
		}
	}
	return res;
}