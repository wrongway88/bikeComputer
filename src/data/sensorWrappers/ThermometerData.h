#ifndef THERMOMETER_DATA_H
#define THERMOMETER_DATA_H

#include "../ISensorData.h"

class ThermometerData : public ISensorData
{
    public:
        ThermometerData();
        virtual ~ThermometerData();

        virtual std::string toString();

        float getTemperature() const;
        void setTemperature(const float temp);

        float getPressure() const;
        void setPressure(const float pressure);

        float getAltitude() const;
        void setAltitude(const float altitude);

        float getSeaLevelPressure() const;
        void setSeaLevelPressure(const float pressure);

    private:
        float m_temperature;
        float m_pressure;
        float m_altitude;
        float m_seaLevelPressure;
};

#endif // THERMOMETER_DATA_H
