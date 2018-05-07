#include "FS1000A_Transmitter.h"

FS1000A_Transmitter::FS1000A_Transmitter()
{

}

FS1000A_Transmitter::~FS1000A_Transmitter()
{

}

void FS1000A_Transmitter::init(uint8_t dataPort, uint16_t bps)
{
	vw_set_ptt_inverted(true);
	vw_setup(bps);
	vw_set_tx_pin(dataPort);
}

void FS1000A_Transmitter::sendMessage(uint8_t* data, uint8_t length)
{
	vw_send(data, length);
}

void FS1000A_Transmitter::waitForFinish()
{
	vw_wait_tx();
}

bool FS1000A_Transmitter::isSent()
{
	return vw_tx_active();
}