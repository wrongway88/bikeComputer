#ifndef ENVIRONMENT_TEMPERATURE_VIEW_H
#define ENVIRONMENT_TEMPERATURE_VIEW_H

#include <FL/Fl_Box.H>

#include <memory>
#include <string>

#include "IView.h"

#include "../data/sensorWrappers/ThermometerData.h"

class EnvironmentTemperatureView : public IView
{
public:
    EnvironmentTemperatureView();
    virtual ~EnvironmentTemperatureView();

    virtual void init(int x, int y);

    virtual bool pushData(const std::shared_ptr<ISensorData>& data);

    int getWidth() const;
    int getHeight() const;

private:
    void handleThermometerData(ThermometerData* data);
    void updateLabel(const std::string& text);

    Fl_Box* m_box;
    std::shared_ptr<std::string> m_labelText;

    int m_width;
    int m_height;

    float m_freezingThreshold;
    float m_coldThreshold;
    float m_warmThreshold;
    float m_hotThreshold;

    Fl_Color m_backgroundColorDefault;
    Fl_Color m_backgroundColorCold;
    Fl_Color m_backgroundColorWarm;
    Fl_Color m_backgroundColorExtreme;
};

#endif // ENVIRONMENT_TEMPERATURE_VIEW_H
