#include "DHT11.h"

DHT11::DHT11(uint8_t dataPin)
{
	this->dataPin = dataPin;
}

DHT11::~DHT11()
{

}

DHT11Data DHT11::getData()
{
	DHT11Data data;
	
	reset();
	data.humidity = readByte();
	readByte();
	data.temperature = readByte();
	readByte();
	
	return data;
}

void DHT11::reset()
{
	digitalWrite(dataPin, LOW);
	pinMode(dataPin, OUTPUT);

	delay(30);

	pinMode(dataPin, INPUT_PULLUP);
	delayMicroseconds(5);

	while (digitalRead(dataPin) == HIGH);
	delayMicroseconds(80);
	while (digitalRead(dataPin) == LOW);
	delayMicroseconds(80);
}

bool DHT11::readBit()
{
	while (digitalRead(dataPin) == HIGH);
	while (digitalRead(dataPin) == LOW);
	
	unsigned long time = micros();
	while (digitalRead(dataPin) == HIGH);
	time = micros() - time;

	return time > 40;
}

uint8_t DHT11::readByte()
{
	uint8_t b = 0;
	for (int i = 0; i < 8; i++)
	{
		b = b << 1;
		b |= readBit();
	}

	return b;
}