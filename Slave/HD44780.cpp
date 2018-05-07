#include "HD44780.h"

HD44780::HD44780(uint8_t rsPin, uint8_t ePin, uint8_t d4Pin, uint8_t d5Pin, uint8_t d6Pin, uint8_t d7Pin)
{
	this->rsPin = rsPin;
	this->ePin = ePin;
	this->d4Pin = d4Pin;
	this->d5Pin = d5Pin;
	this->d6Pin = d6Pin;
	this->d7Pin = d7Pin;
}

HD44780::~HD44780()
{

}

void HD44780::init()
{
	delay(100);

	//Set Register Select to output LOW
	digitalWrite(rsPin, LOW);
	pinMode(rsPin, OUTPUT);

	//Set Enabled to output LOW
	digitalWrite(ePin, LOW);
	pinMode(ePin, OUTPUT);

	//Set data pins to output LOW
	digitalWrite(d4Pin, LOW);
	digitalWrite(d5Pin, LOW);
	digitalWrite(d6Pin, LOW);
	digitalWrite(d7Pin, LOW);

	pinMode(d4Pin, OUTPUT);
	pinMode(d5Pin, OUTPUT);
	pinMode(d6Pin, OUTPUT);
	pinMode(d7Pin, OUTPUT);

	//Start transmission
	//Call Function Set
	write4Bits(0x03);
	delayMicroseconds(4500);

	write4Bits(0x03);
	delayMicroseconds(150);

	write4Bits(0x03);
	delayMicroseconds(100);

	//Call true Function Set and reset to 4bit mode
	write4Bits(0x02);
	delayMicroseconds(100);

	//We are in 4bit mode
	//Set number of lines (2) and font size(5x7)
	write8Bits(0x28);
	delayMicroseconds(100);

	//Display on/off control
	write8Bits(0x08);
	delayMicroseconds(100);

	//Clear Display
	write8Bits(0x01);
	delayMicroseconds(5000);

	//Entry Mode Set (curor increment from left to right, display without shift)
	write8Bits(0x06);
	delayMicroseconds(100);

	//Display on
	write8Bits(0x0C);
	delayMicroseconds(100);
}

void HD44780::pulse()
{
	//SetPinState(E, &PORTB, LOW);
	digitalWrite(ePin, LOW);
	delayMicroseconds(1);

	//SetPinState(E, &PORTB, HIGH);
	digitalWrite(ePin, HIGH);
	delayMicroseconds(1);

	//SetPinState(E, &PORTB, LOW);
	digitalWrite(ePin, LOW);
	delayMicroseconds(100);
}

void HD44780::write4Bits(uint8_t data)
{
	digitalWrite(d7Pin, ((data >> 3) & 0x01));
	digitalWrite(d6Pin, ((data >> 2) & 0x01));
	digitalWrite(d5Pin, ((data >> 1) & 0x01));
	digitalWrite(d4Pin, ((data >> 0) & 0x01));

	pulse();
}

void HD44780::write8Bits(uint8_t data)
{
	write4Bits(data >> 4);
	write4Bits(data);
}

void HD44780::clear()
{
	digitalWrite(rsPin, LOW);
	delayMicroseconds(10);

	//0x01 - clear command
	write8Bits(0x01);
	delay(5);
}

void HD44780::writeChar(char c)
{
	digitalWrite(rsPin, HIGH);
	delayMicroseconds(10);

	write8Bits(c);
	delayMicroseconds(500);
}

void HD44780::writeString(const char* string)
{
	while (*string != '\0')
	{
		writeChar(*string);
		string++;
	}
}

void HD44780::setDDRAM(uint8_t address)
{
	digitalWrite(rsPin, LOW);
	delayMicroseconds(10);

	write8Bits((0x01 << 7) | address);
	delay(5);
}

void HD44780::setLine(uint8_t line)
{
	if (line == 1)
		setDDRAM(0x0);
	else if (line == 2)
		setDDRAM(0x40);
}

void HD44780::cursor(bool show, bool blink)
{
	digitalWrite(rsPin, LOW);
	delayMicroseconds(10);

	write8Bits(0xC | (show << 1) | blink);
	delayMicroseconds(100);
}