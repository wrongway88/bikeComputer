#include <iostream>
#include <memory>
#include <mutex>

#include "data/SensorManager.h"
#include "data/sensorWrappers/GPSWrapper.h"
#include "data/sensorWrappers/ThermometerWrapper.h"
#include "data/sensorWrappers/IRWrapper.h"
#include "data/sensorWrappers/HallSensorWrapper.h"

#include "utility/logging/logging.h"
#include "utility/logging/ConsoleLogger.h"

#include "view/GUIManager.h"

#include "python2.7/Python.h"

SensorManager gSensorManager;

void initLogging();

void sensorThreadFunction();

void setupSensors();
void updateSensors();

void test();

bool gRunSensorUpdates;

std::vector<std::shared_ptr<ISensorData>> gCurrentData;
std::mutex gSensorDataMutex;

GUIManager guiManager;

int main()
{
    initLogging();

    LOG_INFO("Bike Computer");

    gRunSensorUpdates = true;

    std::thread sensorThread(sensorThreadFunction);

    // GUIManager guiManager;
    guiManager.startGUI();

    sensorThread.join();

    return 0;
}

void initLogging()
{
    std::shared_ptr<ConsoleLogger> consoleLogger = std::make_shared<ConsoleLogger>();
    consoleLogger->setLogLevel(Logger::LogLevel::LOG_ALL);
    LogManager::getInstance()->addLogger(consoleLogger);
}

void sensorThreadFunction()
{
    setupSensors();

    Py_BEGIN_ALLOW_THREADS

    while(gRunSensorUpdates)
    {
        updateSensors();
    }

    gSensorManager.stopSensorUpdates();

    Py_END_ALLOW_THREADS
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
    std::vector<std::shared_ptr<ISensorData>> data = gSensorManager.getCurrentSensorData();

    for(auto d : data)
    {
        LOG_INFO(d->toString());
    }

    {
        std::lock_guard<std::mutex> lock(gSensorDataMutex);

        gCurrentData = data;

        guiManager.updateSensorData(gCurrentData);
    }
}

void test()
{
    LOG_INFO("Sensor Test");

    HallSensorWrapper hallWrapper;
    hallWrapper.init();
    hallWrapper.getData();

    LOG_INFO("Sensor Test done");
}
