#ifndef IR_DATA_H
#define IR_DATA_H

#include "../ISensorData.h"

class IRData : public ISensorData
{
    public:
        IRData();
        virtual ~IRData();

        virtual std::string toString();

        float getObjectTemperature() const;
        void setObjectTemperature(const float temperature);

        float getDieTemperature() const;
        void setDieTemperature(const float temperature);

    private:
        float m_objectTemperature;
        float m_dieTemperature;
};

#endif // IR_DATA_H
