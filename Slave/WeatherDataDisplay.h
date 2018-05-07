#pragma once
#include <Arduino.h>
#include "WeatherData.h"
#include "Helpers.h"
#include "StringBuilder.h"

class WeatherDataDisplay
{
public:
	WeatherDataDisplay();
	~WeatherDataDisplay();

	void display(char firstLine[17], char secondLine[17], float internalTemp, WeatherData weatherData);
};