#include "WeatherData.h"

WeatherData::WeatherData()
{

}

WeatherData::~WeatherData()
{

}

void WeatherData::serialise(uint8_t out[BUFFER_SIZE])
{
	byte tmpBuffer[2];

	getBytesFromFloat(tmpBuffer, temperature);
	out[0] = tmpBuffer[0];
	out[1] = tmpBuffer[1];

	getBytesFromFloat(tmpBuffer, pressure - 900);
	out[2] = tmpBuffer[0];
	out[3] = tmpBuffer[1];

	out[4] = humidity;
	out[5] = photoresistor;

	out[6] = uptime >> 8;
	out[7] = uptime & 0xFF;
}

void WeatherData::deserialise(uint8_t data[BUFFER_SIZE])
{
	temperature = getFloatFromBytes(data[0], data[1]);
	pressure = getFloatFromBytes(data[2], data[3]) + 900;
	humidity = data[4];
	photoresistor = data[5];
	uptime = ((uint16_t)data[6] << 8) + data[7];
}

void WeatherData::getBytesFromFloat(uint8_t out[BUFFER_SIZE], float f)
{
	uint16_t converted = f * 10;
	out[0] = converted >> 8;
	out[1] = converted & 0xFF;
}

float WeatherData::getFloatFromBytes(uint8_t firstByte, uint8_t secondByte)
{
	return (((uint16_t)firstByte << 8) | secondByte) / 10.0f;
}

bool WeatherData::isValid()
{
	return (temperature > -30 && temperature < 60) &&
		   (pressure > 980 && pressure < 1050) &&
		   (humidity >= 20 && humidity <= 99) &&
		   (photoresistor >= 0 && humidity <= 99);
}

bool WeatherData::isDeltaValid(WeatherData previousData)
{
	return abs(temperature - previousData.temperature) <= 1 &&
		   abs(pressure - previousData.pressure) <= 2 &&
		   abs((int8_t)humidity - (int8_t)previousData.humidity) <= 10 &&
		   abs((int8_t)uptime - (int8_t)previousData.uptime) <= 1;
}