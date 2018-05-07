#include "Program.h"

Program::Program() : hd(2, 3, 4, 5, 6, 7), displayModeButton(8), ds18b20(10, 12)
{	
	currentDisplay = 0;
	displayUpdateInterval = 200;
	lastDisplayUpdate = 0;

	internalTemperatureInterval = 60000;
	lastInternalTemperatureUpdate = 0;

	internalTemperature = 0;
	timeFromLastReceivedData = 0;

	packetsWithoutError = 0;
}

Program::~Program()
{
	
}

void Program::init()
{
	DEBUG_BEGIN(1000000);

	DEBUG_PRINTLN("WEATHER STATION (slave - debug mode)");
	DEBUG_PRINT("Init devices... ");
	initDevices();
	DEBUG_PRINTLN("[ok]");
	DEBUG_PRINTLN("---------------------------");

	displaySplashScreen();
}

void Program::logic()
{
	if (millis() - lastInternalTemperatureUpdate >= internalTemperatureInterval || lastInternalTemperatureUpdate == 0)
		updateInternalTemperature();

	displayModeButton.logic();
	if (displayModeButton.isClicked())
	{
		currentDisplay = (currentDisplay + 1) % 5;
		updateDisplay();
	}

	if (millis() - lastDisplayUpdate >= (unsigned long)displayUpdateInterval || lastDisplayUpdate == 0)
		updateDisplay();
	
	if (receiver.available())
	{
		uint8_t b[80];
		uint8_t length;
		receiver.getMessage(b, length);

		WeatherData receivedData;
		receivedData.deserialise(b);
		
		DEBUG_PRINT("VALIDATION: ");
		if ((receivedData.isValid() && timeFromLastReceivedData == 0) ||
			(receivedData.isValid() && receivedData.isDeltaValid(currentWeatherData)))
		{
			DEBUG_PRINTLN("OK");
			currentWeatherData = receivedData;
			timeFromLastReceivedData = millis();

			packetsWithoutError++;

			//if(packetsWithoutError > 5)
			//	records.update(internalTemperature, currentWeatherData.temperature, currentWeatherData.pressure);
		}
		else
		{
			DEBUG_PRINTLN("ERROR");

			if (millis() - timeFromLastReceivedData > 200000)
				timeFromLastReceivedData = 0;

			packetsWithoutError = 0;
		}

		printDebugData(receivedData, b);
	}
}

void Program::initDevices()
{
	hd.init();
	ds18b20.init();
	receiver.init(9, 2000);
}

void Program::updateDisplay()
{
	char a[17];
	char b[17];

	if (currentDisplay == 0)
		weatherDataDisplay.display(a, b, internalTemperature, currentWeatherData);
	else if (currentDisplay == 1)
		diagnosticDisplay.display(a, b, (millis() - timeFromLastReceivedData) / 1000, currentWeatherData.uptime, millis() / 3600000);
	else if (currentDisplay == 2)
		minMaxInsideTempDisplay.display(a, b, records.getInsideMinTemp(), records.getInsideMaxTemp());
	else if (currentDisplay == 3)
		minMaxOutsideTempDisplay.display(a, b, records.getOutsideMinTemp(), records.getOutsideMaxTemp());
	else if (currentDisplay == 4)
		minMaxPressureDisplay.display(a, b, records.getMinPressure(), records.getMaxPressure());

	hd.setLine(1);
	hd.writeString(a);
	hd.setLine(2);
	hd.writeString(b);

	lastDisplayUpdate = millis();
}

void Program::displaySplashScreen()
{
	hd.setLine(1);
	hd.writeString("WEATHER  STATION");
	hd.setLine(2);
	hd.writeString("----------------");

	delay(1000);
}

void Program::updateInternalTemperature()
{
	receiver.disableRx();
	internalTemperature = ds18b20.getTemp();
	lastInternalTemperatureUpdate = millis();
	receiver.enableRx();
}

void Program::printDebugData(WeatherData weatherData, uint8_t serialised[WeatherData::BUFFER_SIZE])
{
	DEBUG_PRINTLN();
	DEBUG_PRINT("Temperature (BMP180): ");
	DEBUG_PRINT(weatherData.temperature);
	DEBUG_PRINTLN(" C");

	DEBUG_PRINT("Temperature (DS18B20): ");
	DEBUG_PRINT(internalTemperature);
	DEBUG_PRINTLN(" C");

	DEBUG_PRINT("Pressure (BMP180): ");
	DEBUG_PRINT(weatherData.pressure);
	DEBUG_PRINTLN(" hPa");

	DEBUG_PRINT("Humidity (DHT11): ");
	DEBUG_PRINT(weatherData.humidity);
	DEBUG_PRINTLN(" %");

	DEBUG_PRINT("Photoresistor: ");
	DEBUG_PRINT(weatherData.photoresistor);
	DEBUG_PRINTLN(" %");
	DEBUG_PRINTLN();

#ifdef _DEBUG
	DEBUG_PRINT("Serialised: ");
	for (int i = 0; i < WeatherData::BUFFER_SIZE; i++)
	{
		DEBUG_PRINT(serialised[i]);
		DEBUG_PRINT(' ');
	}
#endif

	DEBUG_PRINTLN();
	DEBUG_PRINT("Free memory: ");
	DEBUG_PRINT(freeMemory());
	DEBUG_PRINTLN(" b");
}