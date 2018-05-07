#include "DS18B20.h"

DS18B20::DS18B20(uint8_t dataPin, uint8_t resolution)
{
	this->dataPin = dataPin;
	this->resolution = resolution;
}

DS18B20::~DS18B20()
{

}

void DS18B20::init()
{
	setResolution(resolution);
}

float DS18B20::getTemp()
{
	reset();
	writeByte(0xCC);
	writeByte(0x44);

	if (resolution == 9) delay(100);
	else if (resolution == 10)  delay(200);
	else if (resolution == 11)  delay(400);
	else if (resolution == 12)  delay(750);

	reset();
	writeByte(0xCC);
	writeByte(0xBE);

	uint8_t t1 = readByte();
	uint8_t t2 = readByte();
	reset();

	return (float)(t1 + (t2 * 256)) / 16;
}

void DS18B20::setResolution(uint8_t resolution)
{
	uint8_t memRes = resolution - 9;
	this->resolution = resolution;

	reset();
	writeByte(0xCC);
	writeByte(0x4E);
	writeByte(0xFF);
	writeByte(0xFF);
	writeByte((memRes << 5) | 0x01f);

	reset();
}

bool DS18B20::isParasitePowerMode()
{
	reset();
	writeByte(0xCC);
	writeByte(0xB4);

	return readByte() == 0;
}

void DS18B20::readDeviceAddress(uint8_t address[8])
{
	reset();
	writeByte(0x33);

	for (int i = 0; i < 8; i++)
	{
		address[i] = readByte();
	}
}

bool DS18B20::isConnected()
{
	return !reset();
}

bool DS18B20::reset()
{
	digitalWrite(dataPin, LOW);
	pinMode(dataPin, OUTPUT);

	delayMicroseconds(480);

	pinMode(dataPin, INPUT);

	delayMicroseconds(45);
	bool presence = digitalRead(dataPin);

	delayMicroseconds(470);
	return presence;
}

void DS18B20::writeBit(char bit)
{
	digitalWrite(dataPin, LOW);
	pinMode(dataPin, OUTPUT);

	delayMicroseconds(5);

	if (bit == 1)
		digitalWrite(dataPin, HIGH);

	delayMicroseconds(60);

	pinMode(dataPin, INPUT);
	delayMicroseconds(5);
}

void DS18B20::writeByte(uint8_t byte)
{
	for (int i = 0; i < 8; i++)
	{
		writeBit((byte >> i) & 0x01);
	}
}

bool DS18B20::readBit()
{
	digitalWrite(dataPin, LOW);
	pinMode(dataPin, OUTPUT);
	delayMicroseconds(2);
	pinMode(dataPin, INPUT);
	delayMicroseconds(5);

	bool bit = digitalRead(dataPin);
	delayMicroseconds(60);

	return bit;
}

uint8_t DS18B20::readByte()
{
	uint8_t result = 0;
	for (int i = 0; i<8; i++)
	{
		bool bit = readBit();
		result |= bit << i;
	}

	return result;
}