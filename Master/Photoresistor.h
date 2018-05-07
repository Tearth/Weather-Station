#pragma once
#include <Arduino.h>

class Photoresistor
{
public:
	Photoresistor(uint8_t dataPin);
	~Photoresistor();

	uint16_t getAbsoluteData();
	float getPercentData();
	float getVoltsData();

private:
	uint8_t dataPin;
};