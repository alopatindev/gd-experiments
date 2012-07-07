#pragma once

#include "ui/MainWindow.h"
#include "ui/Button.h"
#include "libs/sigslot.h"

class MyMainWindow : public MainWindow, public sigslot::has_slots<>
{
    Button * okay;

public:
    MyMainWindow();
    ~MyMainWindow();
    virtual void setup();
    void on_Button_doubleClick();
};
