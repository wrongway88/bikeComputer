#include "HallSensorWrapper.h"

HallSensorWrapper::HallSensorWrapper()
{
}

HallSensorWrapper::~HallSensorWrapper()
{
}

bool HallSensorWrapper::init()
{
    return true;
}

std::shared_ptr<ISensorData> HallSensorWrapper::getData()
{
    return nullptr;
}
