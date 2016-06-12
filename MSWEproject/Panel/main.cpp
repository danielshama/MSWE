#include "Panel.h"
#include "../Label/Label.h"
#include "../TextBox/TextBox.h"
#include "../ComboBox/ComboBox.h"
#include "../NumericBox/NumericBox.h"
#include "../Button/Button.h"
#include "../RadioBox/RadioMaster.h"


HANDLE hStdin;
DWORD fdwSaveOldMode;

VOID ErrorExit(LPSTR);

int main(VOID)
{
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];

	Panel *panel = new Panel(40, 70);
	panel->setLocation(10, 10);
	panel->SetBackground(BackgroundColor::Purple);
	//panel->SetForeground(ForegroundColor::Green);

	Label *label = new Label(10);
	label->setText("text box:");

	TextBox *textBox = new TextBox(20);
	textBox->SetBackground(BackgroundColor::White);
	textBox->SetForeground(ForegroundColor::Teal);
	
	vector<string> vec = { "item1", "item2", "item3", "item4" };
	ComboBox *comboBox = new ComboBox(20, vec);
	comboBox->SetForeground(ForegroundColor::Red);
	comboBox->setPanelBackground(BackgroundColor::Purple);
	comboBox->SetBackground(BackgroundColor::Yellow);

	NumericBox *numericBox = new NumericBox(20, 10, 50);
	numericBox->SetBackground(BackgroundColor::Blue);



	vector<string> itemsOptions = vector<string>({ "This is the first option",
		"This is the second option",
		"This is the third option",
		"This is the fourth option" });

	RadioMaster *radioMaster = new RadioMaster(itemsOptions.size(), 20, itemsOptions);
	radioMaster->SetBackground(BackgroundColor::Yellow);
	radioMaster->SetForeground(ForegroundColor::Blue);

	Button *button = new Button(10);
	button->setText("Noam Gay");
	button->SetBackground(BackgroundColor::Blue);
	button->SetForeground(ForegroundColor::White);

	label->SetBackground(BackgroundColor::Blue);
	label->SetForeground(ForegroundColor::Yellow);

//	panel->addControl(textBox, 15, 2);
	panel->addControl(label, 15, 1);
//	panel->addControl(comboBox, 10, 5);
//	panel->addControl(numericBox, 36, 2);
//	panel->addControl(radioMaster, 40, 10);
	panel->addControl(button, 50, 20);
	panel->draw();

	// Get the standard input handle. 
	hStdin = GetStdHandle(STD_INPUT_HANDLE);
	if (hStdin == INVALID_HANDLE_VALUE)
		ErrorExit("GetStdHandle");

	// Save the current input mode, to be restored on exit. 
	if (!GetConsoleMode(hStdin, &fdwSaveOldMode))
		ErrorExit("GetConsoleMode");

	// Enable the window and mouse input events. 
	fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
	if (!SetConsoleMode(hStdin, fdwMode))
		ErrorExit("SetConsoleMode");

	// Loop to read and handle the next 100 input events. 
	while (true)
	{
		// Wait for the events. 
		if (!ReadConsoleInput(
			hStdin,      // input buffer handle 
			irInBuf,     // buffer to read into 
			128,         // size of read buffer 
			&cNumRead)) // number of records read 
			ErrorExit("ReadConsoleInput");

		// Dispatch the events to the appropriate handler. 
		for (i = 0; i < cNumRead; i++) {
			//Send the input record to the textbox handler
			panel->handleInput(irInBuf[i]);
		}
	}

	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);

	return 0;
}
VOID ErrorExit(LPSTR lpszMessage) {
	fprintf(stderr, "%s\n", lpszMessage);
	// Restore input mode on exit.
	SetConsoleMode(hStdin, fdwSaveOldMode);
	ExitProcess(0);
}

