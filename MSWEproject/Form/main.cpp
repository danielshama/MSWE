#include "Form.h"


int main(VOID)
{
	
	Form *form = new Form();

	Panel *panel = new Panel(40, 70);
	panel->setLocation(10, 10);
	panel->SetBackground(BackgroundColor::Purple);

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

	panel->addControl(textBox, 15, 2);
	panel->addControl(label, 15, 1);
	panel->addControl(comboBox, 10, 5);
	panel->addControl(numericBox, 36, 2);
	panel->addControl(radioMaster, 40, 10);
	//panel->addControl(button, 50, 20);


	form->addPanel(panel);
	form->draw();
	form->run();
	return 0;
}