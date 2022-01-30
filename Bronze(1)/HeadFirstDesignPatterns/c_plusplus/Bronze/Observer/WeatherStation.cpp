#include "WeatherStation.hpp"

using namespace HeadFirstDesignPatterns::Observer;

int main(int argc, char *argv[])
{
	WeatherData *weatherData = new WeatherData();

	CurrentConditionsDisplay *currentDisplay = new CurrentConditionsDisplay(weatherData);
	
	weatherData->setMeasurements(80, 65, 30.4f);
	

	return 0;
}
