#include "DisplayModeButton.h"

DisplayModeButton::DisplayModeButton(uint8_t dataPin)
{
	this->dataPin = dataPin;

	pinMode(dataPin, INPUT_PULLUP);
}

DisplayModeButton::~DisplayModeButton()
{

}

void DisplayModeButton::logic()
{
	bool pinState = digitalRead(dataPin);
	if (!pressed && pinState == LOW)
	{
		pressed = true;
		clicked = true;
	}

	if (pinState == HIGH)
	{
		pressed = false;
		delay(100);
	}
}

bool DisplayModeButton::isClicked()
{
	if (clicked)
	{
		clicked = false;
		return true;
	}

	return false;
}