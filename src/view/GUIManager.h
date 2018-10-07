#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <memory>
#include <thread>
#include <vector>

#include <FL/Fl.H>

#include <vector>
#include "../data/ISensor.h"

#include "IView.h"

class GUIManager
{
    public:
        GUIManager();
        ~GUIManager();

        int startGUI();

        void updateSensorData(const std::vector<std::shared_ptr<ISensorData>>& sensorData);
    private:
        std::vector<std::shared_ptr<IView>> m_views;
};

#endif // GUI_MANAGER_H
