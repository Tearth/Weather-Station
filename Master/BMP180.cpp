#include "BMP180.h"

BMP180::BMP180()
{
	this->resolution = 0;
	this->error = false;
}

BMP180::~BMP180()
{

}

void BMP180::init()
{
	writeBytes(0xAA);	cd.AC_1 = readInt();
	writeBytes(0xAC);	cd.AC_2 = readInt();
	writeBytes(0xAE);	cd.AC_3 = readInt();
	writeBytes(0xB0);	cd.AC_4 = readUInt();
	writeBytes(0xB2);	cd.AC_5 = readUInt();
	writeBytes(0xB4);	cd.AC_6 = readUInt();
	writeBytes(0xB6);	cd.B_1 = readInt();
	writeBytes(0xB8);	cd.B_2 = readInt();
	writeBytes(0xBA);	cd.MB = readInt();
	writeBytes(0xBC);	cd.MC = readInt();
	writeBytes(0xBE);	cd.MD = readInt();
}

float BMP180::getTemp()
{
	int16_t rawTemp = getRawTemp();

	long x1 = (rawTemp - cd.AC_6) * (float)cd.AC_5 / pow(2, 15);
	long x2 = (cd.MC * pow(2, 11)) / (x1 + cd.MD);
	long b5 = x1 + x2;
	long trueTemp = (b5 + 8) / pow(2, 4);

	return (float)trueTemp / 10;
}

float BMP180::getPressure()
{
	long rawTemp = getRawTemp();
	long rawPressure = getRawPressure();

	long p, b3, b6, x3;
	unsigned long b4, b7;

	long x1 = (rawTemp - cd.AC_6) * (float)cd.AC_5 / pow(2, 15);
	long x2 = (cd.MC * pow(2, 11)) / (x1 + cd.MD);
	long b5 = x1 + x2;

	b6 = b5 - 4000;
	x1 = (cd.B_2 * (b6 * b6 / pow(2, 12))) / pow(2, 11);
	x2 = cd.AC_2 * b6 / pow(2, 11);
	x3 = x1 + x2;
	b3 = (((cd.AC_1 * 4 + x3) << resolution) + 2) / 4;
	x1 = cd.AC_3*b6 / pow(2, 13);
	x2 = (cd.B_1 * (b6 * b6 / pow(2, 12))) / pow(2, 16);
	x3 = ((x1 + x2) + 2) / pow(2, 2);
	b4 = cd.AC_4 * (x3 + 32768) / pow(2, 15);
	b7 = (rawPressure - b3) * (50000 >> resolution);
	if (b7 < 0x80000000) { p = (b7 * 2) / b4; }
	else { p = (b7 / b4) * 2; }
	x1 = (p / pow(2, 8)) * (p / pow(2, 8));
	x1 = (x1 * 3038) / pow(2, 16);
	x2 = (-7357 * p) / pow(2, 16);
	p = p + (x1 + x2 + 3791) / pow(2, 4);

	return (float)p / 100;
}

float BMP180::getPressureAtAltitude(int16_t altitude)
{
	return getPressure() / (pow(1 - (altitude / 44330.0f), 5.255));
}

bool BMP180::isError()
{
	return error;
}

uint16_t BMP180::getRawTemp()
{
	uint8_t data[2] = { 0xF4, 0x2E };
	writeBytes(data, 2);
	delay(5);

	writeBytes(0xF6);
	return readUInt();
}

long BMP180::getRawPressure()
{
	uint8_t cmd = 0x34 + (resolution << 6);
	uint8_t data[2] = { 0xF4, cmd };

	writeBytes(data, 2);
	delay(getConversionTime());

	uint8_t bytes[3];
	writeBytes(0xF6);
	readBytes(bytes, 3);

	return (((long)bytes[0] << 16) + ((long)bytes[1] << 8) + bytes[2]) >> (8 - resolution);
}

void BMP180::setresolution(uint8_t resolution)
{
	this->resolution = resolution;
}

void BMP180::beginTransmission()
{
	Wire.beginTransmission(deviceAddress);
}

void BMP180::endTransmission()
{
	error |= Wire.endTransmission() != 0;
}

void BMP180::writeBytes(uint8_t data)
{
	uint8_t data_array[1] = { data };

	beginTransmission();
	Wire.write(data_array, 1);
	endTransmission();
}

void BMP180::writeBytes(uint8_t* data, uint8_t length)
{
	beginTransmission();
	Wire.write(data, length);
	endTransmission();
}

void BMP180::readBytes(uint8_t* data, uint8_t length)
{
	Wire.requestFrom(deviceAddress, length); 
	while (Wire.available() < length);

	Wire.readBytes(data, length);
}

uint16_t BMP180::readUInt()
{
	uint8_t data[2];
	readBytes(data, 2);

	return (uint16_t)(data[0] << 8) | data[1];
}

int16_t BMP180::readInt()
{
	uint8_t data[2];
	readBytes(data, 2);

	return (int16_t)(data[0] << 8) | data[1];
}

uint8_t BMP180::getConversionTime()
{
	switch (resolution)
	{
		case(0): return 5;
		case(1): return 8;
		case(2): return 14;
		case(3): return 26;
	}

	return 0;
}