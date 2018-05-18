#include "ThermometerData.h"

ThermometerData::ThermometerData()
{
}

ThermometerData::~ThermometerData()
{
}

std::string ThermometerData::toString()
{
    std::string result = "Thermometer Data: ";
    result += "Temp: " + std::to_string(m_temperature) + " C°";
    result += " | Alt: " + std::to_string(m_altitude) + " m";
    result += " | Pressure: " + std::to_string(m_pressure);
    result += " | Sea Level Pressure: " + std::to_string(m_seaLevelPressure);

    return result;
}

float ThermometerData::getTemperature() const
{
    return m_temperature;
}

void ThermometerData::setTemperature(const float temp)
{
    m_temperature = temp;
}

float ThermometerData::getPressure() const
{
    return m_pressure;
}

void ThermometerData::setPressure(const float pressure)
{
    m_pressure = pressure;
}

float ThermometerData::getAltitude() const
{
    return m_altitude;
}

void ThermometerData::setAltitude(const float altitude)
{
    m_altitude = altitude;
}

float ThermometerData::getSeaLevelPressure() const
{
    return m_seaLevelPressure;
}

void ThermometerData::setSeaLevelPressure(const float pressure)
{
    m_seaLevelPressure = pressure;
}
