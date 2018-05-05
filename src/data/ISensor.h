#ifndef I_SENSOR_H
#define I_SENSOR_H

#include <memory>

#include "ISensorData.h"

class ISensor
{
	public:
		ISensor(){}
		virtual ~ISensor(){}

        virtual std::shared_ptr<ISensorData> getData() = 0;
};

#endif // I_SENSOR_H
