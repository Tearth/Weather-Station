#pragma once
#include <Arduino.h>
#include "Helpers.h"
#include "StringBuilder.h"

class DiagnosticDisplay
{
public:
	DiagnosticDisplay();
	~DiagnosticDisplay();

	void display(char firstLine[17], char secondLine[17], uint16_t lastReceivedDataTime,
				 uint16_t masterUptime, uint16_t slaveUptime);
};