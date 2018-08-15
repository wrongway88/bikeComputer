#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <memory>
#include <mutex>
#include <thread>
#include <vector>
#include "ISensor.h"

class SensorManager
{
    public:
        SensorManager();
        SensorManager(const SensorManager&) = delete;
        SensorManager& operator=(const SensorManager&) = delete;
        ~SensorManager();

        void pushSensor(std::unique_ptr<ISensor> sensor);

        void startSensorUpdates();
        void stopSensorUpdates();

        std::vector<std::shared_ptr<ISensorData>> getCurrentSensorData();

    private:
        void updateSensorData(ISensor* sensor);

        std::vector<std::unique_ptr<ISensor>> m_sensors;
        std::vector<std::thread> m_sensorThreads;

        std::vector<std::shared_ptr<ISensorData>> m_sensorDataBufferA;
        std::vector<std::shared_ptr<ISensorData>> m_sensorDataBufferB;

        std::vector<std::shared_ptr<ISensorData>>* m_writeBuffer;
        std::vector<std::shared_ptr<ISensorData>>* m_readBuffer;

        bool m_run;
        std::mutex m_bufferMutex;
};

#endif // SENSOR_MANAGER_H
