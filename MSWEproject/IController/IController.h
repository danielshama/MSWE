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


	DWORD backDword;
	DWORD foreDword;

protected:
	HANDLE handle;
	Location loc;

public:
	bool isFocusable;
	bool isFocus;
	bool isVisible;
	DWORD dword;
	DWORD defaulteDword;
	IController(int width) : handle(GetStdHandle(STD_OUTPUT_HANDLE)) { 
		loc.width = width; isVisible = true; isFocusable = true; isFocus = false; 
		CONSOLE_SCREEN_BUFFER_INFO cbi;
		GetConsoleScreenBufferInfo(handle, &cbi);
		defaulteDword = cbi.wAttributes;
		dword = cbi.wAttributes;
	};
	void setLocation(short x, short y) { loc.x = x; loc.y = y; }
	virtual void draw() = 0 ;
	virtual bool handleInput(INPUT_RECORD) = 0;
	~IController() {};

	Location getLocation() { return loc; }
	bool getIsFocusable() { return isFocusable; }
	 
	void SetVisibility(bool visibility) { isVisible = visibility; };
	void SetForeground(ForegroundColor color) {
		foreDword = getForegroundColor(color);
		dword = backDword | foreDword;
	}
	void SetBackground(BackgroundColor color) {
		backDword = getBackgroundColor(color);
		dword = backDword | foreDword;
	};
	void SetBorder(BorderType border);

	boolean checkInLimits(MOUSE_EVENT_RECORD &mer) {
		if (mer.dwMousePosition.X >= loc.x && mer.dwMousePosition.X <= loc.x + loc.width) 
			if (mer.dwMousePosition.Y >= loc.y && mer.dwMousePosition.Y <= loc.y + loc.height - 1) return true;	
		return false;
	}
	//{ Red, Blue, Green, Purple, Teal, Yellow, White, Black };
	DWORD getForegroundColor(ForegroundColor colorF) {
		DWORD color;
		DWORD red, blue, green, intensity;
			red = FOREGROUND_RED;
			blue = FOREGROUND_BLUE;
			green = FOREGROUND_GREEN;
			intensity = FOREGROUND_INTENSITY;

		switch (colorF)
		{
		case ForegroundColor::Red: color = red;   break;
		case ForegroundColor::Blue: color = blue;   break;
		case ForegroundColor::Green: color = green;   break;
		case ForegroundColor::Purple: color = red | blue;   break;
		case ForegroundColor::Teal: color = blue | green;   break;
		case ForegroundColor::Yellow: color = red | green;   break;
		case ForegroundColor::White: color = red | blue | green;   break;
		}
		return color;
	}

	DWORD getBackgroundColor(BackgroundColor colorF) {
		DWORD color;
		DWORD red, blue, green, intensity;
		red = BACKGROUND_RED;
		blue = BACKGROUND_BLUE;
		green = BACKGROUND_GREEN;
		intensity = BACKGROUND_INTENSITY;
		switch (colorF)
		{
		case BackgroundColor::Red: color = red;   break;
		case BackgroundColor::Blue: color = blue;   break;
		case BackgroundColor::Green: color = green;   break;
		case BackgroundColor::Purple: color = red | blue;   break;
		case BackgroundColor::Teal: color = blue | green;   break;
		case BackgroundColor::Yellow: color = red | green;   break;
		case BackgroundColor::White: color = red | blue | green;   break;
		}
		return color;
	}
};

