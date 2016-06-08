#pragma once
#include <Windows.h>
using namespace std;


typedef struct Location {
	short x, y;
	int width, height;
	Location() {}
	Location(short x, short y, int width, int height) 
		: x(x), y(y), width(width), height(height){}
} Location;

enum class ForegroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
enum class BackgroundColor { Red, Blue, Green, Purple, Teal, Yellow, White, Black };
enum class BorderType { Single, Double, None };

class IController {

protected:
	HANDLE handle;
	Location loc;

public:
	bool isFocusable;
	bool isFocus;
	IController(int width) : handle(GetStdHandle(STD_OUTPUT_HANDLE)) { loc.width = width; isFocusable = true; isFocus = false; };
	void setLocation(short x, short y) { loc.x = x; loc.y = y; }
	virtual void draw() = 0 ;
	virtual bool handleInput(INPUT_RECORD) = 0;
	~IController() {};

	Location getLocation() { return loc; }
	bool getIsFocusable() { return isFocusable; }

	void SetVisibility(bool visibility);
	void SetForeground(ForegroundColor color);
	void SetBackground(BackgroundColor color);
	void SetBorder(BorderType border);

	boolean checkInLimits(MOUSE_EVENT_RECORD &mer) {
		if (mer.dwMousePosition.X >= loc.x && mer.dwMousePosition.X <= loc.x + loc.width) 
			if (mer.dwMousePosition.Y >= loc.y && mer.dwMousePosition.Y <= loc.y + loc.height - 1) return true;	
		return false;
	}
};

