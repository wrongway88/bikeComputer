#include "GPSData.h"

GPSData::GPSData()
    : m_latitude(0.0)
    , m_longitude(0.0)
    , m_altitude(0.0)
    , m_speed(0.0)
    , m_climb(0.0)
    , m_heading(0.0)
    , m_timeStamp(0.0)
{}

GPSData::~GPSData()
{}

std::string GPSData::toString()
{
    std::string result = "GPS Data";
    result += ": " + std::to_string(m_latitude) + "/" + std::to_string(m_longitude);
    result += " | " + std::to_string(m_altitude) + "m";
    result += " | v: " + std::to_string(m_speed) + " cl: " + std::to_string(m_climb);
    result += " | hdng: " + std::to_string(m_heading);
    return result;
}

void GPSData::setLatitude(const double latitude)
{
    m_latitude = latitude;
}

double GPSData::getLatitude() const
{
    return m_latitude;
}

void GPSData::setLongitude(const double longitude)
{
    m_longitude = longitude;
}

double GPSData::getLongitude() const
{
    return m_longitude;
}

void GPSData::setAltitude(const double altitude)
{
    m_altitude = altitude;
}

double GPSData::getAltitude() const
{
    return m_altitude;
}

void GPSData::setSpeed(const double speed)
{
    m_speed = speed;
}

double GPSData::getSpeed() const
{
    return m_speed;
}

void GPSData::setClimb(const double climb)
{
    m_climb = climb;
}

double GPSData::getClimb() const
{
    return m_climb;
}

void GPSData::setHeading(const double heading)
{
    m_heading = heading;
}

double GPSData::getHeading() const
{
    return m_heading;
}

void GPSData::setTimeStamp(const timestamp_t timeStamp)
{
    m_timeStamp = timeStamp;
}

timestamp_t GPSData::getTimeStamp() const
{
    return m_timeStamp;
}
