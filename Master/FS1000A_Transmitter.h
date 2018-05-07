#pragma once
#include <VirtualWire.h>

class FS1000A_Transmitter
{
public:
	FS1000A_Transmitter();
	~FS1000A_Transmitter();

	void init(uint8_t dataPort, uint16_t bps);
	void sendMessage(uint8_t* data, uint8_t length);
	void waitForFinish();
	bool isSent();

private:
};