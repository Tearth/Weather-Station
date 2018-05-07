#pragma once
#include <Arduino.h>

struct DHT11Data
{
	uint8_t temperature;
	uint8_t humidity;
};

class DHT11
{
public:
	DHT11(uint8_t dataPin);
	~DHT11();

	//Returns humidity and temperature
	DHT11Data getData();

private:
	uint8_t dataPin;

	void reset();
	bool readBit();
	uint8_t readByte();
};