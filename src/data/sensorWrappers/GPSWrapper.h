#ifndef GPS_WRAPPER_H
#define GPS_WRAPPER_H

#include "libgpsmm.h"

#include "../ISensor.h"

class GPSWrapper : public ISensor
{
	public:
		GPSWrapper();
		virtual ~GPSWrapper();

        virtual bool init();

		virtual std::shared_ptr<ISensorData> getData();

    private:
        gpsmm m_gpsRecorder;
};

#endif // GPS_WRAPPER_H
