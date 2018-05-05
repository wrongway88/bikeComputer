#ifndef GPS_WRAPPER_H
#define GPS_WRAPPER_H

#include "../ISensor.h"

class GPSWrapper : public ISensor
{
	public:
		GPSWrapper();
		virtual ~GPSWrapper();

		virtual std::shared_ptr<ISensorData> getData();
};

#endif // GPS_WRAPPER_H
