#include <iostream>
#include <memory>

#include "data/SensorManager.h"
#include "data/sensorWrappers/GPSWrapper.h"
#include "data/sensorWrappers/ThermometerWrapper.h"
#include "data/sensorWrappers/IRWrapper.h"
#include "data/sensorWrappers/HallSensorWrapper.h"

#include "utility/logging/logging.h"
#include "utility/logging/ConsoleLogger.h"

#include "view/TestView.h"

#include <FL/Fl.H>

#include "python2.7/Python.h"

SensorManager gSensorManager;

void initLogging();

void setupSensors();
void updateSensors();

void test();

int main()
{
    initLogging();

    LOG_INFO("Bike Computer");

    setupSensors();

    Py_BEGIN_ALLOW_THREADS

    while(true)
    {
        updateSensors();
    }

    gSensorManager.stopSensorUpdates();

    Py_END_ALLOW_THREADS

	// test();

	// TestView testView;
	// testView.openTestWindow();

	return Fl::run();
}

void initLogging()
{
    std::shared_ptr<ConsoleLogger> consoleLogger = std::make_shared<ConsoleLogger>();
    consoleLogger->setLogLevel(Logger::LogLevel::LOG_ALL);
    LogManager::getInstance()->addLogger(consoleLogger);
}

void setupSensors()
{
    LOG_INFO("Sensor setup");

    std::unique_ptr<ThermometerWrapper> thermometer = std::make_unique<ThermometerWrapper>();
    thermometer->init();
    gSensorManager.pushSensor(std::move(thermometer));

    std::unique_ptr<GPSWrapper> gps = std::make_unique<GPSWrapper>();
    while(gps->init() == false)
    {
        sleep(100);
    }
    gSensorManager.pushSensor(std::move(gps));

    std::unique_ptr<IRWrapper> irSensor = std::make_unique<IRWrapper>();
    irSensor->init();
    gSensorManager.pushSensor(std::move(irSensor));

    LOG_INFO("Sensors ready");

    gSensorManager.startSensorUpdates();
}

void updateSensors()
{
    auto data = gSensorManager.getCurrentSensorData();

    // LOG_INFO_STREAM(<< data.size() << " data points");

    for(auto d : data)
    {
        LOG_INFO(d->toString());
    }
}

void test()
{
    LOG_INFO("Sensor Test");

    HallSensorWrapper hallWrapper;
    hallWrapper.init();
    hallWrapper.getData();

    /*
    ThermometerWrapper tw;
    tw.init();
    std::string dataString = tw.getData()->toString();
    LOG_INFO(dataString);


    IRWrapper irw;
    irw.init();
    std::string irString = irw.getData()->toString();
    LOG_INFO(irString);
    */


    /*
    GPSWrapper gpsw;
    while(gpsw.init() == false)
    {
    }
    std::string gpsString = gpsw.getData()->toString();
    LOG_INFO(gpsString);
    */


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
