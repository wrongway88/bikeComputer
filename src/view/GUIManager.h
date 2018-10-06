#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <thread>

#include <FL/Fl.H>

#include "TestView.h"

#include <vector>
#include "../data/ISensor.h"

class GUIManager
{
    public:
        GUIManager();
        ~GUIManager();

        int startGUI();

        void updateSensorData(const std::vector<std::shared_ptr<ISensorData>>& sensorData);
    private:
        TestView m_testView;
};

#endif // GUI_MANAGER_H
