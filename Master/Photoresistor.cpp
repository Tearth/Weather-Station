#include "Photoresistor.h"

Photoresistor::Photoresistor(uint8_t dataPin)
{
	this->dataPin = dataPin;
}

Photoresistor::~Photoresistor()
{

}

uint16_t Photoresistor::getAbsoluteData()
{
	return analogRead(dataPin);
}

float Photoresistor::getPercentData()
{
	return analogRead(dataPin) * (100 / 1024.0f);
}

float Photoresistor::getVoltsData()
{
	return analogRead(dataPin) * (5 / 1024.0f);
}