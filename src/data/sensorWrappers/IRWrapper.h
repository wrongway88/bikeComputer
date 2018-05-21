#ifndef IR_WRAPPER_H
#define IR_WRAPPER_H

#include "../ISensor.h"

#include "python2.7/Python.h"

class IRWrapper : public ISensor
{
    public:
        IRWrapper();
		virtual ~IRWrapper();

        virtual bool init();

		virtual std::shared_ptr<ISensorData> getData();

    private:
        float getObjectTemperature();
        float getDieTemperature();

        PyObject* m_pyGetObjTemp;
        PyObject* m_pyGetDieTemp;
};

#endif // IR_WRAPPER_H
