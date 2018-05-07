#include "Helpers.h"

int16_t getIntegerPart(float number)
{
	return (int16_t)number;
}

uint16_t getDecimalPart(float number, uint8_t precision)
{
	uint16_t m = pow(10, precision);
	return (uint16_t)(abs(number * m)) % m;
}

uint8_t getNumberLength(int16_t number)
{
	if (number == 0)
		return 1;

	uint8_t length = 0;
	if (number < 0)
		length++;

	while (number != 0)
	{
		number /= 10;
		length++;
	}

	return length;
}

uint8_t getNumberLength(float number, uint8_t precision)
{
	uint8_t length = precision + 1;
	int16_t fixedNumber = (int16_t)number;
	
	length += getNumberLength((int16_t)number);

	return length;
}