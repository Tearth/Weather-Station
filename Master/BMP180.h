#pragma once
#include <Arduino.h>
#include <Wire.h>

struct BMPcd
{
	int16_t AC_1;
	int16_t AC_2;
	int16_t AC_3;
	uint16_t AC_4;
	uint16_t AC_5;
	uint16_t AC_6;
	int16_t B_1;
	int16_t B_2;
	int16_t MB;
	int16_t MC;
	int16_t MD;
};

class BMP180
{
public:
	BMP180();
	~BMP180();

	void init();
	float getTemp();
	float getPressure();
	float getPressureAtAltitude(int16_t altitude);

	void setresolution(uint8_t resolution);
	bool isError();
private:
	const uint8_t deviceAddress = 0x77;
	uint8_t resolution;
	bool error;
	BMPcd cd;

	void beginTransmission();
	void endTransmission();
	uint8_t getConversionTime();

	uint16_t getRawTemp();
	long getRawPressure();

	void writeBytes(uint8_t data);
	void writeBytes(uint8_t* data, uint8_t length);
	void readBytes(uint8_t* data, uint8_t length);
	uint16_t readUInt();
	int16_t readInt();
};