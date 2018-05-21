#include <iostream>
#include <memory>

#include "data/SensorManager.h"
#include "data/sensorWrappers/GPSWrapper.h"
#include "data/sensorWrappers/ThermometerWrapper.h"
#include "data/sensorWrappers/IRWrapper.h"

#include "utility/logging/logging.h"
#include "utility/logging/ConsoleLogger.h"

SensorManager gSensorManager;

void initLogging();
void test();

int main()
{
    initLogging();

    LOG_INFO("Bike Computer");

	test();

	return 0;
}

void initLogging()
{
    std::shared_ptr<ConsoleLogger> consoleLogger = std::make_shared<ConsoleLogger>();
    consoleLogger->setLogLevel(Logger::LogLevel::LOG_ALL);
    LogManager::getInstance()->addLogger(consoleLogger);
}

void test()
{
    LOG_INFO("Sensor Test");

    ThermometerWrapper tw;
    tw.init();
    std::string dataString = tw.getData()->toString();
    LOG_INFO(dataString);


    IRWrapper irw;
    irw.init();
    std::string irString = irw.getData()->toString();
    LOG_INFO(irString);


    /*
    std::unique_ptr<GPSWrapper> gpsWrapper = std::make_unique<GPSWrapper>();

    while(gpsWrapper->init())
    {
        Sleep(100);
    }
    */

    // gSensorManager.pushSensor(gpsWrapper);

    // .pu

    /*
    GPSWrapper gps;
    gps.init();
    std::string gpsDataString = gps.getData()->toString();

    LOG_INFO(gpsDataString);
    */

    LOG_INFO("Sensor Test done");
}

