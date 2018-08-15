#include "SensorManager.h"

#include <unistd.h>

#include "../utility/logging/logging.h"

SensorManager::SensorManager()
    : m_sensors()
    , m_sensorThreads()
    , m_sensorDataBufferA()
    , m_sensorDataBufferB()
    , m_writeBuffer(&m_sensorDataBufferA)
    , m_readBuffer(&m_sensorDataBufferB)
    , m_run(false)
    , m_bufferMutex()
{
}

SensorManager::~SensorManager()
{
}

void SensorManager::pushSensor(std::unique_ptr<ISensor> sensor)
{
    m_sensors.push_back(std::move(sensor));
}

void SensorManager::startSensorUpdates()
{
    m_run = true;

    for(auto itr = m_sensors.begin(); itr != m_sensors.end(); itr++)
    {
        m_sensorThreads.push_back(std::thread(&SensorManager::updateSensorData, this, (*itr).get()));
    }
}

void SensorManager::stopSensorUpdates()
{
    m_run = false;

    for(auto itr = m_sensorThreads.begin(); itr != m_sensorThreads.end(); itr++)
    {
        itr->join();
    }
}

std::vector<std::shared_ptr<ISensorData>> SensorManager::getCurrentSensorData()
{
    std::vector<std::shared_ptr<ISensorData>> result;

    {
        std::lock_guard<std::mutex> lock(m_bufferMutex);
        auto tmp = m_writeBuffer;
        m_writeBuffer = m_readBuffer;
        m_readBuffer = tmp;
    }

    for(std::shared_ptr<ISensorData> sensorData : *m_readBuffer)
    {
        result.push_back(sensorData);
    }

    m_readBuffer->clear();

    return result;
}

void SensorManager::updateSensorData(ISensor* sensor)
{
    while(m_run)
    {
        std::shared_ptr<ISensorData> data = sensor->getData();

        if(data != nullptr)
        {
            std::lock_guard<std::mutex> lock(m_bufferMutex);
            m_writeBuffer->push_back(data);
        }
        // sleep(100); // sleep does not return??
    }
}
