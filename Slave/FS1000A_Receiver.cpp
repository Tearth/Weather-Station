#include "FS1000A_Receiver.h"

FS1000A_Receiver::FS1000A_Receiver()
{

}

FS1000A_Receiver::~FS1000A_Receiver()
{
	
}

void FS1000A_Receiver::init(uint8_t dataPort, uint16_t bps)
{
	vw_set_ptt_inverted(true);
	vw_setup(bps);
	vw_set_rx_pin(dataPort);
	
	enableRx();
}

bool FS1000A_Receiver::available()
{
	return vw_have_message();
}

bool FS1000A_Receiver::getMessage(uint8_t buffer[VW_MAX_MESSAGE_LEN], uint8_t& length)
{
	return vw_get_message(buffer, &length);
}

void FS1000A_Receiver::waitForMessage()
{
	vw_wait_rx();
}

void FS1000A_Receiver::waitForMessage(uint16_t timeout)
{
	vw_wait_rx_max(timeout);
}

uint8_t FS1000A_Receiver::getBadMessagesCount()
{
	return vw_get_rx_bad();
}

uint8_t FS1000A_Receiver::getGoodMessagesCount()
{
	return vw_get_rx_good();
}

void FS1000A_Receiver::enableRx()
{
	vw_rx_start();
}

void FS1000A_Receiver::disableRx()
{
	vw_rx_stop();
}