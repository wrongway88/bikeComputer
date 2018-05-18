#include "ThermometerWrapper.h"
#include "ThermometerData.h"
#include "../../utility/logging/logging.h"

ThermometerWrapper::ThermometerWrapper()
    : m_pyGetTemp(nullptr)
    , m_pyGetPressure(nullptr)
    , m_pyGetAltitude(nullptr)
    , m_pyGetSeaLevelPressure(nullptr)
{
}

ThermometerWrapper::~ThermometerWrapper()
{
    Py_DECREF(m_pyGetTemp);
    Py_DECREF(m_pyGetPressure);
    Py_DECREF(m_pyGetAltitude);
    Py_DECREF(m_pyGetSeaLevelPressure);
    Py_Finalize();
}

bool ThermometerWrapper::init()
{
    Py_Initialize();

    static const std::string initBMP180 =
        "import Adafruit_BMP.BMP085 as BMP085";

    static const std::string getTempFunction =
        "def getTemp():\
            return sensor.read_temperature();";
    static const std::string getPressureFunction =
        "def getPressure():\
            return sensor.read_pressure();";
    static const std::string getAltitudeFunction =
        "def getAltitude():\
            return sensor.read_altitude();";
    static const std::string getSeaLevelPressureFunction =
        "def getSeaLevelPressure():\
            return sensor.read_sealevel_pressure();";

    int res = PyRun_SimpleString(initBMP180.c_str());

    res = res | PyRun_SimpleString("sensor = BMP085.BMP085()");
    res = res | PyRun_SimpleString(getTempFunction.c_str());
    res = res | PyRun_SimpleString(getPressureFunction.c_str());
    res = res | PyRun_SimpleString(getAltitudeFunction.c_str());
    res = res | PyRun_SimpleString(getSeaLevelPressureFunction.c_str());

    if(res != 0)
    {
        LOG_ERROR("Failed to parse python functions.");
        return false;
    }

    PyObject* mainModule = PyImport_AddModule("__main__");
    PyObject* globalDict = PyModule_GetDict(mainModule);

    m_pyGetTemp = PyDict_GetItemString(globalDict, "getTemp");
    m_pyGetPressure = PyDict_GetItemString(globalDict, "getPressure");
    m_pyGetAltitude = PyDict_GetItemString(globalDict, "getAltitude");
    m_pyGetSeaLevelPressure = PyDict_GetItemString(globalDict, "getSeaLevelPressure");

    if(m_pyGetTemp == nullptr
        || m_pyGetPressure == nullptr
        || m_pyGetAltitude == nullptr
        || m_pyGetSeaLevelPressure == nullptr)
    {
        LOG_ERROR("Failed to get handlers to python functions");

        return false;
    }

    // PyObject* result =  PyObject_CallObject(expression, nullptr);

    // PyIntObject* intResult = dynamic_cast<PyIntObject*>(result);

    // long resValue = PyInt_AsLong(result);

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
    if(m_pyGetTemp == nullptr)
    {
        LOG_ERROR("Python function not initialized.");
        return 0.0f;
    }

    PyObject* result =  PyObject_CallObject(m_pyGetTemp, nullptr);
    return PyFloat_AsDouble(result);
}

float ThermometerWrapper::getPressure()
{
    if(m_pyGetPressure == nullptr)
    {
        LOG_ERROR("Python function not initialized.");
        return 0.0f;
    }

    PyObject* result =  PyObject_CallObject(m_pyGetPressure, nullptr);
    return PyFloat_AsDouble(result);
}

float ThermometerWrapper::getAltitude(float seaLevelPressure)
{
    if(m_pyGetAltitude == nullptr)
    {
        LOG_ERROR("Python function not initialized.");
        return 0.0f;
    }

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyFloat_FromDouble(seaLevelPressure));

    // TODO: pass argument
    PyObject* result =  PyObject_CallObject(m_pyGetAltitude, nullptr);
    return PyFloat_AsDouble(result);
}

float ThermometerWrapper::getSeaLevelPressure(float altitude)
{
    if(m_pyGetSeaLevelPressure == nullptr)
    {
        LOG_ERROR("Python function not initialized.");
        return 0.0f;
    }

    PyObject* args = PyTuple_New(1);
    PyTuple_SetItem(args, 0, PyFloat_FromDouble(altitude));

    // TODO: pass argument
    PyObject* result =  PyObject_CallObject(m_pyGetSeaLevelPressure, nullptr);
    return PyFloat_AsDouble(result);
}
