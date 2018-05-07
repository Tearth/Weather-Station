#pragma once
#include <Arduino.h>
#include <eeprom.h>

class Records
{
public:
	Records();
	~Records();

	void update(float insideTemp, float outsideTemp, float pressure);
	float getInsideMinTemp();
	float getInsideMaxTemp();
	float getOutsideMinTemp();
	float getOutsideMaxTemp();
	float getMinPressure();
	float getMaxPressure();

	void saveInsideMinTemp(float temp);
	void saveInsideMaxTemp(float temp);
	void saveOutsideMinTemp(float temp);
	void saveOutsideMaxTemp(float temp);
	void saveMinPressure(float pressure);
	void saveMaxPressure(float pressure);

private:
};