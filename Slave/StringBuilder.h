#pragma once
#include <Arduino.h>
#include "Helpers.h"

class StringBuilder
{
public:
	StringBuilder(uint16_t size);
	~StringBuilder();

	void append(char* data);
	void append(uint16_t data);
	void append(float data);

	void appendSequence(char data, uint16_t count);
	void clear();
	uint16_t getPointer();

	char* string;

private:
	uint16_t pointer;
	uint16_t size;
};