#include "GUIManager.h"

#include <sstream>

#include "../utility/logging/logging.h"

#include "../data/sensorWrappers/ThermometerData.h"

GUIManager::GUIManager()
{}

GUIManager::~GUIManager()
{}

int GUIManager::startGUI()
{
	m_testView.openTestWindow();

    return Fl::run();
}

void GUIManager::updateSensorData(const std::vector<std::shared_ptr<ISensorData>>& sensorData)
{
    for(std::shared_ptr<ISensorData> data : sensorData)
    {
        // get thermometer data
        ThermometerData* thermometerData = dynamic_cast<ThermometerData*>(data.get());

        if(thermometerData != nullptr)
        {
            std::stringstream labelStream;
            labelStream << thermometerData->getTemperature();

            m_testView.updateLabel(labelStream.str());
        }
    }
}
