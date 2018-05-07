#include "Program.h"

Program::Program() : dht11(4), photoresistor(A1)/*, windSpeed(A0)*/
{
	lastSendTime = 0;
	sendTimeInterval = 15000;

	//Photoresistor settings
	pinMode(A2, OUTPUT);
	digitalWrite(A2, HIGH);
	pinMode(A0, OUTPUT);
	digitalWrite(A0, LOW);
	
	//DHT11 settings
	pinMode(3, OUTPUT);
	digitalWrite(3, HIGH);
	pinMode(5, OUTPUT);
	digitalWrite(5, LOW);
}

Program::~Program()
{

}

void Program::init()
{
	DEBUG_BEGIN(1000000);

	DEBUG_PRINTLN("WEATHER STATION (master - debug mode)");
	DEBUG_PRINT("Init devices... ");
	initDevices();
	DEBUG_PRINTLN("[ok]");
	DEBUG_PRINTLN("---------------------------");
}

void Program::logic()
{
	if (millis() - lastSendTime >= sendTimeInterval || lastSendTime == 0)
	{
		lastSendTime = millis();

		WeatherData weatherData;

		do {
			weatherData.temperature = bmp180.getTemp();
			delay(200);
			weatherData.pressure = bmp180.getPressureAtAltitude(180);
			delay(200);
			weatherData.humidity = dht11.getData().humidity;
			delay(200);
			weatherData.photoresistor = photoresistor.getPercentData();
			delay(200);
			weatherData.uptime = millis() / 3600000;
			delay(1000);
		} while (!weatherData.isValid());

		uint8_t serialisedData[WeatherData::BUFFER_SIZE];
		weatherData.serialise(serialisedData);
		sendToSlave(serialisedData);

		printDebugData(weatherData, serialisedData);
	}
}

void Program::initDevices()
{
	bmp180.init();
	transmitter.init(2, 2000);
}

void Program::sendToSlave(uint8_t data[WeatherData::BUFFER_SIZE])
{
	transmitter.sendMessage(data, WeatherData::BUFFER_SIZE);
}

void Program::printDebugData(WeatherData weatherData, uint8_t serialised[WeatherData::BUFFER_SIZE])
{
	DEBUG_PRINT("Temperature (BMP180): ");
	DEBUG_PRINT(weatherData.temperature);
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
}