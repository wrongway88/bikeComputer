#include "ThermometerWrapper.h"
#include "ThermometerData.h"
#include "../../utility/logging/logging.h"
#include "../../utility/python/PythonWrapper.h"

ThermometerWrapper::ThermometerWrapper()
    : m_pyGetTemp(nullptr)
    , m_pyGetPressure(nullptr)
    , m_pyGetAltitude(nullptr)
    , m_pyGetSeaLevelPressure(nullptr)
{
}

ThermometerWrapper::~ThermometerWrapper()
{
    PythonWrapper* python = PythonWrapper::getInstance();
    python->releaseItem(m_pyGetTemp);
    python->releaseItem(m_pyGetPressure);
    python->releaseItem(m_pyGetAltitude);
    python->releaseItem(m_pyGetSeaLevelPressure);
}

bool ThermometerWrapper::init()
{
    static const std::string initBMP180 =
        "import Adafruit_BMP.BMP085 as BMP085";

    static const std::string getTempFunction =
        "def getTemp():\
            return tempSensor.read_temperature();";
    static const std::string getPressureFunction =
        "def getPressure():\
            return tempSensor.read_pressure();";
    static const std::string getAltitudeFunction =
        "def getAltitude():\
            return tempSensor.read_altitude();";
    static const std::string getSeaLevelPressureFunction =
        "def getSeaLevelPressure():\
            return tempSensor.read_sealevel_pressure();";

    PythonWrapper* python = PythonWrapper::getInstance();

    int res = python->runString(initBMP180);

    res = res | python->runString("tempSensor = BMP085.BMP085()");
    res = res | python->runString(getTempFunction);
    res = res | python->runString(getPressureFunction);
    res = res | python->runString(getAltitudeFunction);
    res = res | python->runString(getSeaLevelPressureFunction);

    if(res != 0)
    {
        LOG_ERROR("Failed to parse python functions.");
        return false;
    }

    m_pyGetTemp = python->getItem("getTemp");
    m_pyGetPressure = python->getItem("getPressure");
    m_pyGetAltitude = python->getItem("getAltitude");
    m_pyGetSeaLevelPressure = python->getItem("getSeaLevelPressure");

    if(m_pyGetTemp == nullptr
        || m_pyGetPressure == nullptr
        || m_pyGetAltitude == nullptr
        || m_pyGetSeaLevelPressure == nullptr)
    {
        LOG_ERROR("Failed to get handlers to python functions");

        return false;
    }

    return true;
}

std::shared_ptr<ISensorData> ThermometerWrapper::getData()
{
    std::shared_ptr<ThermometerData> result = std::make_shared<ThermometerData>();

    result->setPressure(getPressure());
    result->setAltitude(getAltitude());
    result->setTemperature(getTemperature());
    result->setSeaLevelPressure(getSeaLevelPressure());

    return result;
}

float ThermometerWrapper::getTemperature()
{
    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetTemp, result) == false)
    {
        LOG_ERROR("Failed to read temperature");
    }

    return result;
}

float ThermometerWrapper::getPressure()
{
    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetPressure, result) == false)
    {
        LOG_ERROR("Failed to read air pressure");
    }

    return result;
}

float ThermometerWrapper::getAltitude(float seaLevelPressure)
{
    // TODO: pass argument

    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetAltitude, result) == false)
    {
        LOG_ERROR("Failed to read altitude");
    }

    return result;
}

float ThermometerWrapper::getSeaLevelPressure(float altitude)
{
    // TODO: pass argument
    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetSeaLevelPressure, result) == false)
    {
        LOG_ERROR("Failed to read sea level pressure");
    }

    return result;
}
