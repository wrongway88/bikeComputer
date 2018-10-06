#ifndef TEST_VIEW_H
#define TEST_VIEW_H

#include <FL/Fl_Box.H>

#include <memory>
#include <string>

class TestView
{
    public:
        TestView();
        ~TestView();

        void openTestWindow();

        void updateLabel(const std::string& text);

    private:
        Fl_Box* box;

        std::shared_ptr<std::string> m_labelText;
};

#endif // TEST_VIEW_H
