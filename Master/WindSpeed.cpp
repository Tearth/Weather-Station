#include "WindSpeed.h"

WindSpeed::WindSpeed(uint8_t dataPin)
{
	this->dataPin = dataPin;
}

WindSpeed::~WindSpeed()
{

}

float WindSpeed::getRotations(uint16_t measurementTime, uint8_t vanes)
{
	unsigned long measurementTimeStart = millis();
	uint16_t rotations = 0;
	float edge = 1.5f;
	bool lightMode = (analogRead(dataPin) * 5.0f) / 1024 >= edge ? true : false;

	float voltage = 0;

	while (millis() - measurementTimeStart < measurementTime)
	{
		voltage = (analogRead(dataPin) * 5.0f) / 1024;
		if (voltage >= edge + 0.2f && !lightMode)
		{
			rotations++;
			lightMode = true;
		}

		if (voltage < edge && lightMode)
			lightMode = false;
	}

	return (float)rotations / vanes;
}