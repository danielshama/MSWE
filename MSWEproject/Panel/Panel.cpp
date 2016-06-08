#include "Panel.h"


DWORD regularAttr;

Panel::Panel(int height, int width) : IController(width)
{
	loc.height = height;
	CONSOLE_CURSOR_INFO cci = { 100, FALSE };
	SetConsoleCursorInfo(handle, &cci);
	CONSOLE_SCREEN_BUFFER_INFO cbi;
	GetConsoleScreenBufferInfo(handle, &cbi);
	regularAttr = cbi.wAttributes;
}

bool Panel::handleInput(INPUT_RECORD ir) {



	return true;
}

Panel::~Panel()
{
}

void Panel::addControl(IController *controller, short x, short y) {
	controller->setLocation(loc.x + x, loc.y + y);
	Location locTemp = controller->getLocation();
	if (checkAvailableLocation(locTemp.x, locTemp.y, locTemp.width, locTemp.height)) {
		if (controllers.size() == 0)
			if (controller->getIsFocusable())
				controller->isFocus = true;
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
	}
	SetConsoleCursorPosition(handle, { loc.x, loc.y + (short)loc.height });
	cout << frameLength;
	SetConsoleCursorPosition(handle, { loc.x, loc.y });
	SetConsoleTextAttribute(handle, regularAttr);
	for (int i = 0; i < controllers.size(); i++) {
		controllers[i]->draw();
	}
}