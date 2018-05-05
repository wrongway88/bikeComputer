#ifndef GPS_DATA_H
#define GPS_DATA_H

#include "../ISensorData.h"

class GPSData : public ISensorData
{
    public:
        GPSData();
        virtual ~GPSData();

        virtual std::string toString();
};

#endif // GPS_DATA_H
