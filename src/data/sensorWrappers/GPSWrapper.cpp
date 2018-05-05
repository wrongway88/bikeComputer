#include "GPSWrapper.h"

#include "GPSData.h"



GPSWrapper::GPSWrapper()
    : m_gpsRecorder("localhost", DEFAULT_GPSD_PORT)
{
}

GPSWrapper::~GPSWrapper()
{
}

bool GPSWrapper::init()
{
    if(m_gpsRecorder.stream(WATCH_ENABLE | WATCH_JSON) == nullptr)
    {
        return false;
    }

    return true;
}

std::shared_ptr<ISensorData> GPSWrapper::getData()
{
    return std::make_shared<GPSData>();
}
