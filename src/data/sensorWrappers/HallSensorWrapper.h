#ifndef HALL_SENSOR_WRAPPER_H
#define HALL_SENSOR_WRAPPER_H

#include "../ISensor.h"

class HallSensorWrapper : public ISensor
{
    public:
        HallSensorWrapper();
        virtual ~HallSensorWrapper();

        virtual bool init();

		virtual std::shared_ptr<ISensorData> getData();

    private:

};

#endif // HALL_SENSOR_WRAPPER_H
