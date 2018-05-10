#include <iostream>
#include <memory>

#include "data/sensorWrappers/GPSWrapper.h"
#include "utility/logging/logging.h"
#include "utility/logging/ConsoleLogger.h"

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
    LOG_INFO("GPS Test");

    GPSWrapper gps;
    gps.init();
    std::string gpsDataString = gps.getData()->toString();

    LOG_INFO(gpsDataString);

    LOG_INFO("GPS Test done");
}

