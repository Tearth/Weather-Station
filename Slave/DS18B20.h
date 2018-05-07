#pragma once
#include <Arduino.h>

class DS18B20
{
public:
	DS18B20(uint8_t dataPin, uint8_t resolution);
	~DS18B20();

	void init();

	//Reads temperature from sensor. Conversion times:
	// 9 bits resolution - ~100ms
	// 10 bits resolution - ~200ms
	// 11 bits resolution - ~400ms
	// 12 bits resolution - ~750ms
	float getTemp();

	//Sets temperature resolution (9/10/11/12 bits)
	void setResolution(uint8_t resolution);

	//Returns true if there is parasite power mode
	bool isParasitePowerMode();

	//Reads device address and fills passed array
	void readDeviceAddress(uint8_t address[8]);

	//Returns true if there is connected device
	bool isConnected();
private:
	uint8_t dataPin;
	uint8_t resolution;

	bool reset();

	void writeBit(char bit);
	void writeByte(uint8_t byte);

	bool readBit();
	uint8_t readByte();
};