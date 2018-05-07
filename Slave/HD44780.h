#pragma once
#include <Arduino.h>

class HD44780
{
public:
	HD44780(uint8_t rsPin, uint8_t ePin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin);
	~HD44780();

	void init();

	//Pulses the Enable pin
	void pulse();

	//Sends 4 bytes to the device
	void write4Bits(uint8_t data);

	//Sends 8 bytes (two packets of 4 bytes)
	void write8Bits(uint8_t data);

	//Clears display
	void clear();

	//Writes single char at display
	void writeChar(char c);

	//Writes string at display (must be ended with \0)
	void writeString(const char* string);

	//Sets cursor position to specific address
	void setDDRAM(uint8_t address);

	//Sets cursor at begin of specific line
	void setLine(uint8_t line);

	//Sets cursor parameters
	void cursor(bool show, bool blink);

private:
	uint8_t rsPin;
	uint8_t ePin;
	uint8_t d4Pin;
	uint8_t d5Pin;
	uint8_t d6Pin;
	uint8_t d7Pin;
};