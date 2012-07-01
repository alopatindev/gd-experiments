#pragma once

#include "Widget.h"

class MainWindow : public Widget
{
    bool m_fullscreen;

public:
    MainWindow();
    void setFullscreen(bool fullscreen = true);
    void run();
    virtual void setup();
};
