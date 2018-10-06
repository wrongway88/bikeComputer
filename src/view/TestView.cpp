#include "TestView.h"

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

TestView::TestView()
    : box(nullptr)
    , m_labelText(nullptr)
{
}

TestView::~TestView()
{
}

void TestView::openTestWindow()
{
    m_labelText = std::make_shared<std::string>("temp");

    Fl_Window* window = new Fl_Window(340, 180);
    box = new Fl_Box(20, 40, 300, 100, m_labelText->c_str());
    box->box(FL_UP_BOX);
    box->labelfont(FL_BOLD + FL_ITALIC);
    box->labelsize(36);
    box->labeltype(FL_SHADOW_LABEL);
    // box->label("");

    window->end();
    window->show();
}

void TestView::updateLabel(const std::string& text)
{
    if(box != nullptr)
    {
        *m_labelText = text;
        box->label(m_labelText->c_str());
    }
}
