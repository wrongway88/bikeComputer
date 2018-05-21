#include "IRData.h"

IRData::IRData()
{
}

IRData::~IRData()
{
}

std::string IRData::toString()
{
    std::string result = "IR Data";
    result += ": Object Temp: " + std::to_string(m_objectTemperature);
    result += ": Die Temp: " + std::to_string(m_dieTemperature);

    return result;
}

float IRData::getObjectTemperature() const
{
    return m_objectTemperature;
}

void IRData::setObjectTemperature(const float temperature)
{
    m_objectTemperature = temperature;
}

float IRData::getDieTemperature() const
{
    return m_dieTemperature;
}

void IRData::setDieTemperature(const float temperature)
{
    m_dieTemperature = temperature;
}
