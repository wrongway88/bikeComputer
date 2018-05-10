#ifndef GPS_DATA_H
#define GPS_DATA_H

#include "../ISensorData.h"

typedef double timestamp_t;

class GPSData : public ISensorData
{
    public:
        GPSData();
        virtual ~GPSData();

        virtual std::string toString();

        void setLatitude(const double latitude);
        double getLatitude() const;

        void setLongitude(const double longitude);
        double getLongitude() const;

        void setAltitude(const double altitude);
        double getAltitude() const;

        void setSpeed(const double speed);
        double getSpeed() const;

        void setClimb(const double climb);
        double getClimb() const;

        void setHeading(const double heading);
        double getHeading() const;

        void setTimeStamp(const timestamp_t timeStamp);
        timestamp_t getTimeStamp() const;

    private:
        double m_latitude;
        double m_longitude;
        double m_altitude;
        double m_speed;
        double m_climb;
        double m_heading;

        timestamp_t m_timeStamp;
};

#endif // GPS_DATA_H
