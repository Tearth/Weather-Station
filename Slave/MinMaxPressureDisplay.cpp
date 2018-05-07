#include "MinMaxPressureDisplay.h"

MinMaxPressureDisplay::MinMaxPressureDisplay()
{

}

MinMaxPressureDisplay::~MinMaxPressureDisplay()
{

}

void MinMaxPressureDisplay::display(char firstLine[17], char secondLine[17], float minPressure, float maxPressure)
{
	memset(firstLine, 0, 17);
	memset(secondLine, 0, 17);

	StringBuilder firstLineBuilder(17);
	firstLineBuilder.append("Max pres: ");
	firstLineBuilder.append(maxPressure);

	StringBuilder secondLineBuilder(17);
	secondLineBuilder.append("Min pres: ");
	secondLineBuilder.append(minPressure);

	memcpy(firstLine, firstLineBuilder.string, 17);
	memcpy(secondLine, secondLineBuilder.string, 17);
}