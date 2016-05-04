#pragma once
#include "../IController/IController.h"

class IControllerInput : public IController
{
public:
	IControllerInput(short x, short y) : IController(x, y) {}
	~IControllerInput() {}
	virtual void handleInput(INPUT_RECORD) {}
};

