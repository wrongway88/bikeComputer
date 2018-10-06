#include "IRWrapper.h"
#include "IRData.h"
#include "../../utility/logging/logging.h"
#include "../../utility/python/PythonWrapper.h"

IRWrapper::IRWrapper()
{
}

IRWrapper::~IRWrapper()
{
    PythonWrapper* python = PythonWrapper::getInstance();
    python->releaseItem(m_pyGetObjTemp);
    python->releaseItem(m_pyGetDieTemp);
}

bool IRWrapper::init()
{
    static const std::string initTMP006 =
        "import Adafruit_TMP.TMP006 as TMP006";
    static const std::string getObjTempFunction =
        "def getIRObjTemp():\
            return irSensor.readObjTempC();";
    static const std::string getDieTempFunction =
        "def getIRDieTemp():\
            return irSensor.readDieTempC();";

    PythonWrapper* python = PythonWrapper::getInstance();

    int res = python->runString(initTMP006);
    res = res | python->runString("irSensor = TMP006.TMP006()");
    res = res | python->runString("irSensor.begin()");
    res = res | python->runString(getObjTempFunction);
    res = res | python->runString(getDieTempFunction);

    if(res != 0)
    {
        LOG_ERROR("Failed to parse python functions.");
        return false;
    }

    m_pyGetObjTemp = python->getItem("getIRObjTemp");
    m_pyGetDieTemp = python->getItem("getIRDieTemp");

    if(m_pyGetObjTemp == nullptr
        || m_pyGetDieTemp == nullptr)
    {
        LOG_ERROR("Failed to get handlers to python functions");

        return false;
    }

    LOG_INFO("IR Sensor initialized");

    return true;
}

std::shared_ptr<ISensorData> IRWrapper::getData()
{
    std::shared_ptr<IRData> result = std::make_shared<IRData>();

    result->setObjectTemperature(getObjectTemperature());
    result->setDieTemperature(getDieTemperature());

    return result;
}

float IRWrapper::getObjectTemperature()
{
    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetObjTemp, result) == false)
    {
        LOG_ERROR("Failed to read object temperature");
    }

    return result;
}

float IRWrapper::getDieTemperature()
{
    float result = 0.0f;
    if(PythonWrapper::getInstance()->callFunctionObject(m_pyGetDieTemp, result) == false)
    {
        LOG_ERROR("Failed to read die temperature");
    }

    return result;
}
