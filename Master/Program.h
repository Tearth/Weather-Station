#pragma once
#include <Arduino.h>

#include "DebugMacros.h"
#include "BMP180.h"
#include "DHT11.h"
#include "Photoresistor.h"
#include "WeatherData.h"
#include "FS1000A_Transmitter.h"
#include "WindSpeed.h"

class Program
{
public:
	Program();
	~Program();

	void init();
	void logic();

private:
	BMP180 bmp180;
	DHT11 dht11;
	Photoresistor photoresistor;
	FS1000A_Transmitter transmitter;
	//WindSpeed windSpeed;

	unsigned long lastSendTime;
	uint16_t sendTimeInterval;

	void initDevices();
	void sendToSlave(uint8_t data[WeatherData::BUFFER_SIZE]);
	void printDebugData(WeatherData data, uint8_t serialised[WeatherData::BUFFER_SIZE]);
};