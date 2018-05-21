#include "PythonWrapper.h"

#include "../logging/logging.h"

PythonWrapper* PythonWrapper::m_instance = nullptr;

PythonWrapper* PythonWrapper::getInstance()
{
    if(m_instance == nullptr)
    {
        m_instance = new PythonWrapper();

        m_instance->init();
    }

    return m_instance;
}

int PythonWrapper::runString(const std::string& text)
{
    return PyRun_SimpleString(text.c_str());
}

PyObject* PythonWrapper::getItem(const std::string& name)
{
    PyObject* result = nullptr;

    if(m_globalDict != nullptr)
    {
        result = PyDict_GetItemString(m_globalDict, name.c_str());
    }
    else
    {
        LOG_ERROR("Dictionary not found!");
    }

    return result;
}

void PythonWrapper::releaseItem(PyObject* item)
{
    Py_DECREF(item);
}

bool PythonWrapper::callFunctionObject(PyObject* function, float& result)
{
    if(function == nullptr)
    {
        LOG_ERROR("Python function not initialized.");
        return false;
    }

    PyObject* resultObject =  PyObject_CallObject(function, nullptr);
    result = PyFloat_AsDouble(resultObject);

    return true;
}

PythonWrapper::PythonWrapper()
{
}

PythonWrapper::~PythonWrapper()
{
    if(m_instance != nullptr)
    {
        Py_Finalize();

        delete m_instance;
    }
}

void PythonWrapper::init()
{
    Py_Initialize();

    m_mainModule = PyImport_AddModule("__main__");
    m_globalDict = PyModule_GetDict(m_mainModule);
}
