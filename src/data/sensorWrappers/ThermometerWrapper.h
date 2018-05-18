#ifndef THERMOMETER_WRAPPER_H
#define THERMOMETER_WRAPPER_H

#include "../ISensor.h"

#include "python2.7/Python.h"

class ThermometerWrapper : public ISensor
{
    public:
        ThermometerWrapper();
        virtual ~ThermometerWrapper();

        virtual bool init();

        virtual std::shared_ptr<ISensorData> getData();

    private:
        float getTemperature();
        float getPressure();
        float getAltitude(float seaLevelPressure = 101325.0f);
        float getSeaLevelPressure(float altitude = 0.0f);

        PyObject* m_pyGetTemp;
        PyObject* m_pyGetPressure;
        PyObject* m_pyGetAltitude;
        PyObject* m_pyGetSeaLevelPressure;
};

#endif // THERMOMETER_WRAPPER_H
