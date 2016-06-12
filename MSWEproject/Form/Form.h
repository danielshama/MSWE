#pragma once
#include "../Panel/Panel.h"
#include "../Label/Label.h"
#include "../TextBox/TextBox.h"
#include "../ComboBox/ComboBox.h"
#include "../NumericBox/NumericBox.h"
#include "../Button/Button.h"
#include "../RadioBox/RadioMaster.h"

class Form
{

	HANDLE hStdin;
	DWORD fdwSaveOldMode;
	vector<Panel*> panels;

	void focusOnNextPanel();
	bool checkFreeSpace(Panel* panel);
	int getFocusedPanel();
	void ErrorExit(LPSTR lpszMessage);

public:
	Form();
	~Form();

	bool addPanel(Panel* panel);
	void draw();
	void run();
};

