#include "DiagnosticDisplay.h"

DiagnosticDisplay::DiagnosticDisplay()
{

}

DiagnosticDisplay::~DiagnosticDisplay()
{

}

void DiagnosticDisplay::display(char firstLine[17], char secondLine[17], uint16_t lastReceivedDataTime, 
								uint16_t masterUptime, uint16_t slaveUptime)
{
	memset(firstLine, 0, 17);
	memset(secondLine, 0, 17);

	StringBuilder firstLineBuilder(17);
	firstLineBuilder.append("Last update:");
	if (lastReceivedDataTime > 999)
		firstLineBuilder.append(" inf");
	else
	{
		firstLineBuilder.appendSequence(' ', 16 - (getNumberLength(lastReceivedDataTime) + 1) - firstLineBuilder.getPointer());
		firstLineBuilder.append((uint16_t)lastReceivedDataTime);
		firstLineBuilder.append("s");
	}

	StringBuilder secondLineBuilder(17);
	secondLineBuilder.append("Up: M:");
	secondLineBuilder.append((uint16_t)masterUptime);
	secondLineBuilder.appendSequence(' ', 16 - (getNumberLength(slaveUptime) + 2) - secondLineBuilder.getPointer());
	secondLineBuilder.append("S:");
	secondLineBuilder.append((uint16_t)slaveUptime);

	memcpy(firstLine, firstLineBuilder.string, 17);
	memcpy(secondLine, secondLineBuilder.string, 17);
}