#ifndef I_SENSOR_DATA_H
#define I_SENSOR_DATA_H

#include <string>

class ISensorData
{
    public:
        ISensorData(){}
        virtual ~ISensorData(){}

        virtual std::string toString() = 0;
};

#endif // I_SENSOR_DATA_H
