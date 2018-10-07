#include "GUIManager.h"

#include <sstream>

#include <FL/Fl_Window.H>

#include "../utility/logging/logging.h"

#include "../data/sensorWrappers/ThermometerData.h"

#include "EnvironmentTemperatureView.h"

GUIManager::GUIManager()
    : m_views()
{}

GUIManager::~GUIManager()
{}

int GUIManager::startGUI()
{
    Fl_Window* window = new Fl_Window(340, 280);
    window->color(FL_BLACK);

    std::shared_ptr<EnvironmentTemperatureView> temperatureView = std::make_shared<EnvironmentTemperatureView>();
    temperatureView->init(20, 20);
    m_views.push_back(temperatureView);

	window->end();
    window->show();

    return Fl::run();
}

void GUIManager::updateSensorData(const std::vector<std::shared_ptr<ISensorData>>& sensorData)
{
    for(std::shared_ptr<ISensorData> data : sensorData)
    {
        for(std::shared_ptr<IView> view : m_views)
        {
            view->pushData(data);
        }
    }
}
