#include "MinMaxOutsideTempDisplay.h"

MinMaxOutsideTempDisplay::MinMaxOutsideTempDisplay()
{

}

MinMaxOutsideTempDisplay::~MinMaxOutsideTempDisplay()
{

}

void MinMaxOutsideTempDisplay::display(char firstLine[17], char secondLine[17], float minTemp, float maxTemp)
{
	memset(firstLine, 0, 17);
	memset(secondLine, 0, 17);

	StringBuilder firstLineBuilder(17);
	firstLineBuilder.append("MaxOtemp: ");
	firstLineBuilder.append(maxTemp);

	StringBuilder secondLineBuilder(17);
	secondLineBuilder.append("MinOtemp: ");
	secondLineBuilder.append(minTemp);

	memcpy(firstLine, firstLineBuilder.string, 17);
	memcpy(secondLine, secondLineBuilder.string, 17);
}