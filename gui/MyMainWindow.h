#pragma once

#include "ui/MainWindow.h"
#include "ui/Button.h"

class MyMainWindow : public MainWindow
{
    Button * okay;

public:
    MyMainWindow();
    ~MyMainWindow();
    virtual void setup();
};
