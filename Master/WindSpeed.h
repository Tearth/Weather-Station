#pragma once
#include <Arduino.h>

class WindSpeed
{
public:
	WindSpeed(uint8_t dataPin);
	~WindSpeed();

	float getRotations(uint16_t measurementTime, uint8_t vanes);

private:
	uint8_t dataPin;
};