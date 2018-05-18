#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#include <memory>
#include <vector>
#include "ISensor.h"

class SensorManager
{
    public:
        SensorManager();
        ~SensorManager();

        void pushSensor();

    private:
        std::vector<std::unique_ptr<ISensor>> m_sensors;
};

#endif // SENSOR_MANAGER_H
