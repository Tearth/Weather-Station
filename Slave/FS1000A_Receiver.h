#pragma once
#include <VirtualWire.h>

class FS1000A_Receiver
{
public:
	FS1000A_Receiver();
	~FS1000A_Receiver();

	void init(uint8_t dataPort, uint16_t bps);
	bool available();
	bool getMessage(uint8_t buffer[VW_MAX_MESSAGE_LEN], uint8_t& length);
	void waitForMessage();
	void waitForMessage(uint16_t timeout);
	void enableRx();
	void disableRx();

	uint8_t getBadMessagesCount();
	uint8_t getGoodMessagesCount();
private:

};