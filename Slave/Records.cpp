#include "Records.h"

Records::Records()
{
	saveInsideMinTemp(99);
	saveInsideMaxTemp(-99);
	saveOutsideMinTemp(99);
	saveOutsideMaxTemp(-99);
	saveMinPressure(1300);
	saveMaxPressure(800);
}

Records::~Records()
{

}

void Records::update(float insideTemp, float outsideTemp, float pressure)
{
	if (insideTemp < getInsideMinTemp())
		saveInsideMinTemp(insideTemp);
	if (insideTemp > getInsideMaxTemp())
		saveInsideMaxTemp(insideTemp);

	if (outsideTemp < getOutsideMinTemp())
		saveOutsideMinTemp(outsideTemp);
	if (outsideTemp > getOutsideMaxTemp())
		saveOutsideMaxTemp(outsideTemp);

	if (pressure < getMinPressure())
		saveMinPressure(pressure);
	if (pressure > getMaxPressure())
		saveMaxPressure(pressure);
}

float Records::getInsideMinTemp()
{
	int16_t rawTemp = eeprom_read_word((uint16_t*)0);
	return (float)rawTemp / 10;
}

float Records::getInsideMaxTemp()
{
	int16_t rawTemp = eeprom_read_word((uint16_t*)2);
	return (float)rawTemp / 10;
}

float Records::getOutsideMinTemp()
{
	int16_t rawTemp = eeprom_read_word((uint16_t*)4);
	return (float)rawTemp / 10;
}

float Records::getOutsideMaxTemp()
{
	int16_t rawTemp = eeprom_read_word((uint16_t*)6);
	return (float)rawTemp / 10;
}

float Records::getMinPressure()
{
	int16_t rawPressure = eeprom_read_word((uint16_t*)8);
	return (float)rawPressure / 10;
}

float Records::getMaxPressure()
{
	int16_t rawPressure = eeprom_read_word((uint16_t*)10);
	return (float)rawPressure / 10;
}

void Records::saveInsideMinTemp(float temp)
{
	int16_t rawTemp = temp * 10;
	eeprom_update_word((uint16_t*)0, rawTemp);
}

void Records::saveInsideMaxTemp(float temp)
{
	int16_t rawTemp = temp * 10;
	eeprom_update_word((uint16_t*)2, rawTemp);
}

void Records::saveOutsideMinTemp(float temp)
{
	int16_t rawTemp = temp * 10;
	eeprom_update_word((uint16_t*)4, rawTemp);
}

void Records::saveOutsideMaxTemp(float temp)
{
	int16_t rawTemp = temp * 10;
	eeprom_update_word((uint16_t*)6, rawTemp);
}

void Records::saveMinPressure(float pressure)
{
	int16_t rawPressure = pressure * 10;
	eeprom_update_word((uint16_t*)8, rawPressure);
}

void Records::saveMaxPressure(float pressure)
{
	int16_t rawPressure = pressure * 10;
	eeprom_update_word((uint16_t*)10, rawPressure);
}