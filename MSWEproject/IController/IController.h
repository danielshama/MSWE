#pragma once
#include <Windows.h>
using namespace std;


typedef struct {
	short x, y;
	int width, height;
} location;

enum class ForegroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
enum class BackgroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
enum class BorderType { Single, Double, None };

class IController {

protected:
	HANDLE handle;
	COORD c;
	location loc;

public:
	bool isFocusable;
	bool isFocus;
	IController(int width) : handle(GetStdHandle(STD_OUTPUT_HANDLE)) { loc.width = width; isFocusable = true; isFocus = false; };
	void setLocation(short x, short y) { c = { x, y }; }
	virtual void draw() = 0 ;
	virtual void handleInput(INPUT_RECORD) = 0;
	~IController() {};

	void SetVisibility(bool visibility);
	location getLocation() { return loc; }
	bool getIsFocusable() { return isFocusable; }
	void SetForeground(ForegroundColor color);
	void SetBackground(BackgroundColor color);
	void SetBorder(BorderType border);
	boolean checkInLimits(MOUSE_EVENT_RECORD &mer) {
		if (mer.dwMousePosition.X >= loc.x && mer.dwMousePosition.X <= loc.x + loc.width) 
			if (mer.dwMousePosition.Y >= loc.y && mer.dwMousePosition.Y <= loc.y + loc.height - 1) return true;	
		return false;
	}
};

