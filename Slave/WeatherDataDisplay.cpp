#include "WeatherDataDisplay.h"

WeatherDataDisplay::WeatherDataDisplay()
{

}

WeatherDataDisplay::~WeatherDataDisplay()
{

}

void WeatherDataDisplay::display(char firstLine[17], char secondLine[17], float internalTemp, WeatherData weatherData)
{
	memset(firstLine, 0, 17);
	memset(secondLine, 0, 17);
	
	StringBuilder firstLineBuilder(17);
	firstLineBuilder.append("I:");
	firstLineBuilder.append(internalTemp);
	firstLineBuilder.appendSequence(' ', 16 - (getNumberLength(weatherData.temperature, 1) + 2) - firstLineBuilder.getPointer());
	firstLineBuilder.append("O:");
	firstLineBuilder.append(weatherData.temperature);

	StringBuilder secondLineBuilder(17);
	secondLineBuilder.append("H:");
	secondLineBuilder.append((uint16_t)weatherData.humidity);
	secondLineBuilder.appendSequence(' ', 5 - secondLineBuilder.getPointer());
	secondLineBuilder.append(weatherData.pressure);
	secondLineBuilder.appendSequence(' ', 16 - (getNumberLength(weatherData.photoresistor) + 2) - secondLineBuilder.getPointer());
	secondLineBuilder.append("I:");
	secondLineBuilder.append((uint16_t)weatherData.photoresistor);

	memcpy(firstLine, firstLineBuilder.string, 17);
	memcpy(secondLine, secondLineBuilder.string, 17);
}