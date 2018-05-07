#pragma once
#include <Arduino.h>

class WeatherData
{
public:
	WeatherData();
	~WeatherData();

	static const uint8_t BUFFER_SIZE = 8;
	void serialise(uint8_t out[BUFFER_SIZE]);
	void deserialise(uint8_t out[BUFFER_SIZE]);
	bool isValid();
	bool isDeltaValid(WeatherData previousData);

	float temperature;
	float pressure;
	uint8_t humidity;
	uint8_t photoresistor;
	uint16_t uptime;

private:
	void getBytesFromFloat(uint8_t out[BUFFER_SIZE], float f);
	float getFloatFromBytes(uint8_t firstByte, uint8_t secondByte);
};