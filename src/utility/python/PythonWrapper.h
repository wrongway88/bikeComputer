#ifndef PYTHON_WRAPPER_H
#define PYTHON_WRAPPER_H

#include <memory>

#include "python2.7/Python.h"

class PythonWrapper
{
    public:
        static PythonWrapper* getInstance();

        int runString(const std::string& text);

        PyObject* getItem(const std::string& name);

        void releaseItem(PyObject* item);

        bool callFunctionObject(PyObject* function, float& result);

    private:
        static PythonWrapper* m_instance;

        PythonWrapper();
        ~PythonWrapper();

        void init();

        PyObject* m_mainModule;
        PyObject* m_globalDict;
};

#endif // PYTHON_WRAPPER_H
