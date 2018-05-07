#include "StringBuilder.h"

StringBuilder::StringBuilder(uint16_t size)
{
	this->size = size;

	string = new char[size];
	clear();
}

StringBuilder::~StringBuilder()
{
	delete[] string;
}

void StringBuilder::append(char* data)
{
	char *ptr = data;
	while(*ptr != '\0')
	{
		string[pointer] = *ptr;
		pointer++;

		ptr++;
	}
}

void StringBuilder::append(uint16_t data)
{
	uint8_t numberLength = getNumberLength(data);
	char* numberArray = new char[numberLength];
	sprintf(numberArray, "%d", data); 

	for (int i = 0; i < numberLength; i++)
	{
		string[pointer] = numberArray[i];
		pointer++;
	}

	delete[] numberArray;
}

void StringBuilder::append(float data)
{
	int16_t integerPart = getIntegerPart(data);
	int16_t decimalPart = getDecimalPart(data, 1);

	uint8_t totalLength = getNumberLength(data, 1);

	char* numberArray = new char[totalLength];
	sprintf(numberArray, "%d.%d", integerPart, decimalPart);

	for (int i = 0; i < totalLength; i++)
	{
		string[pointer] = numberArray[i];
		pointer++;
	}

	delete[] numberArray;
}

void StringBuilder::appendSequence(char data, uint16_t count)
{
	for (int i = 0; i < count; i++)
	{
		string[pointer] = data;
		pointer++;
	}
}

void StringBuilder::clear()
{
	pointer = 0;
	memset(string, ' ', size);
	string[size - 1] = '\0';
}

uint16_t StringBuilder::getPointer()
{
	return pointer;
}