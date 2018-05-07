#pragma once
#include <Arduino.h>

class DisplayModeButton
{
public:
	DisplayModeButton(uint8_t dataPin);
	~DisplayModeButton();

	void logic();
	bool isClicked();

private:
	uint8_t dataPin;
	bool pressed;
	bool clicked;
};