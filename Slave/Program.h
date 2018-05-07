#pragma once
#include <Arduino.h>

#include "DebugMacros.h"
#include "HD44780.h"
#include "DS18B20.h"
#include "FS1000A_Receiver.h"
#include "WeatherData.h"
#include "DisplayModeButton.h"
#include "WeatherDataDisplay.h"
#include "DiagnosticDisplay.h"
#include "MinMaxInsideTempDisplay.h"
#include "MinMaxOutsideTempDisplay.h"
#include "MinMaxPressureDisplay.h"
#include "Records.h"
#include <MemoryFree.h>

class Program
{
public:
	Program();
	~Program();

	void init();
	void logic();

private:
	HD44780 hd;
	DS18B20 ds18b20;
	FS1000A_Receiver receiver;
	WeatherData currentWeatherData;
	DisplayModeButton displayModeButton;

	WeatherDataDisplay weatherDataDisplay;
	DiagnosticDisplay diagnosticDisplay;
	MinMaxInsideTempDisplay minMaxInsideTempDisplay;
	MinMaxOutsideTempDisplay minMaxOutsideTempDisplay;
	MinMaxPressureDisplay minMaxPressureDisplay;

	Records records;

	uint8_t currentDisplay;
	uint16_t displayUpdateInterval;
	unsigned long lastDisplayUpdate;

	uint16_t internalTemperatureInterval;
	unsigned long lastInternalTemperatureUpdate;
	float internalTemperature;

	unsigned long timeFromLastReceivedData;
	uint16_t packetsWithoutError;

	void initDevices();
	void displaySplashScreen();
	void updateDisplay();

	void updateInternalTemperature();
	void printDebugData(WeatherData weatherData, uint8_t serialised[WeatherData::BUFFER_SIZE]);
};