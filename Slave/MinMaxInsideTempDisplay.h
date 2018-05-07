#pragma once
#include <Arduino.h>
#include "Helpers.h"
#include "StringBuilder.h"

class MinMaxInsideTempDisplay
{
public:
	MinMaxInsideTempDisplay();
	~MinMaxInsideTempDisplay();

	void display(char firstLine[17], char secondLine[17], float minTemp, float maxTemp);
};