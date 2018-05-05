#include <iostream>

#include "data/sensorWrappers/GPSWrapper.h"

void test();

int main()
{
	std::cout << "Bike Computer" << std::endl;

	return 0;
}

void test()
{
    GPSWrapper gps;
    gps.init();
    gps.getData();
}

