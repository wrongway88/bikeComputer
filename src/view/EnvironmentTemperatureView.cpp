#include "EnvironmentTemperatureView.h"

#include <sstream>

EnvironmentTemperatureView::EnvironmentTemperatureView()
    : m_box(nullptr)
    , m_labelText(nullptr)
    , m_width(100)
    , m_height(40)
    , m_freezingThreshold(0.0f)
    , m_coldThreshold(12.0f)
    , m_warmThreshold(25.0f)
    , m_hotThreshold(30.0f)
    , m_backgroundColorDefault(FL_BLACK)
    , m_backgroundColorCold(FL_BLUE)
    , m_backgroundColorWarm(FL_YELLOW)
    , m_backgroundColorExtreme(FL_RED)
{}

EnvironmentTemperatureView::~EnvironmentTemperatureView()
{}

void EnvironmentTemperatureView::init(int x, int y)
{
    m_labelText = std::make_shared<std::string>("N/A");

    m_box = new Fl_Box(x, y, m_width, m_height, m_labelText->c_str());
    m_box->box(FL_UP_BOX);
    m_box->labelsize(20);
    m_box->color(FL_BLACK);
    m_box->labelcolor(FL_WHITE);

    // m_box->col
}

bool EnvironmentTemperatureView::pushData(const std::shared_ptr<ISensorData>& data)
{
    ThermometerData* tData = dynamic_cast<ThermometerData*>(data.get());

    if(tData != nullptr)
    {
        handleThermometerData(tData);
    }

    return true;
}

int EnvironmentTemperatureView::getWidth() const
{
    return m_width;
}

int EnvironmentTemperatureView::getHeight() const
{
    return m_height;
}

void EnvironmentTemperatureView::handleThermometerData(ThermometerData* data)
{
    float temperature = data->getTemperature();
    std::stringstream sstream;
    sstream << temperature;

    updateLabel(sstream.str());

    Fl_Color oldColor = m_box->color();

    Fl_Color newColor = FL_BLACK;
    if(temperature < m_freezingThreshold)
    {
        newColor = m_backgroundColorExtreme;
    }
    else if(temperature < m_coldThreshold)
    {
        newColor = m_backgroundColorCold;
    }
    else if(temperature < m_warmThreshold)
    {
        newColor = m_backgroundColorDefault;
    }
    else if(temperature < m_hotThreshold)
    {
        newColor = m_backgroundColorWarm;
    }
    else
    {
        newColor = m_backgroundColorExtreme;
    }

    if(oldColor != newColor)
    {
        m_box->color(newColor);
        m_box->redraw();
    }
}

void EnvironmentTemperatureView::updateLabel(const std::string& text)
{
    if(m_box != nullptr && m_labelText != nullptr)
    {
        *m_labelText = text;
        m_box->label(m_labelText->c_str());
    }
}
