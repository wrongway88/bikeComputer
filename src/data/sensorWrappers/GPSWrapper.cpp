#include "GPSWrapper.h"

#include "GPSData.h"

#include "../../utility/logging/logging.h"

GPSWrapper::GPSWrapper()
    : m_gpsRecorder("localhost", DEFAULT_GPSD_PORT)
{
}

GPSWrapper::~GPSWrapper()
{
}

bool GPSWrapper::init()
{
    LOG_INFO("initializing");

    // TODO: delay until GPSD is initialized
    int result = system("stty -F/dev/ttyAMA0 9600");

    result = system("sudo gpsd /dev/ttyAMA0 -F/var/run/gpsd.sock");

    if(m_gpsRecorder.stream(WATCH_ENABLE | WATCH_JSON) == nullptr)
    {
        LOG_ERROR("GPS initialization failed");
        return false;
    }

    LOG_INFO("GPS initialized");

    return true;
}

std::shared_ptr<ISensorData> GPSWrapper::getData()
{
    std::shared_ptr<GPSData> result = std::make_shared<GPSData>();

    gps_data_t* gpsData;

    if(!m_gpsRecorder.waiting(50000000))
    {
        LOG_ERROR("GPS timed out");
        return result;
    }

    if((gpsData = m_gpsRecorder.read()) == nullptr)
    {
        LOG_ERROR("GPS read fail");
        return result;
    }
    else
    {
        while(((gpsData = m_gpsRecorder.read()) == nullptr)
            || (gpsData->fix.mode < 1))
        {
            // just wait I guess?
        }

        timestamp_t timeStamp = gpsData->fix.time;
        double lat = gpsData->fix.latitude;
        double lon = gpsData->fix.longitude;

        result->setLatitude(gpsData->fix.latitude);
        result->setLongitude(gpsData->fix.longitude);
        result->setAltitude(gpsData->fix.altitude);
        result->setSpeed(gpsData->fix.speed);
        result->setClimb(gpsData->fix.climb);
        result->setHeading(gpsData->fix.track);
        result->setTimeStamp(gpsData->fix.time);
    }


    return result;
}
