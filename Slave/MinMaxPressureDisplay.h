#pragma once
#include <Arduino.h>
#include "Helpers.h"
#include "StringBuilder.h"

class MinMaxPressureDisplay
{
public:
	MinMaxPressureDisplay();
	~MinMaxPressureDisplay();

	void display(char firstLine[17], char secondLine[17], float minPressure, float maxPressure);
};