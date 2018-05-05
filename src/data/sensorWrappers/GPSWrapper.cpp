#include "GPSWrapper.h"

#include "GPSData.h"

GPSWrapper::GPSWrapper()
{
}

GPSWrapper::~GPSWrapper()
{
}

std::shared_ptr<ISensorData> GPSWrapper::getData()
{
    return std::make_shared<GPSData>();
}
