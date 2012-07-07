#pragma once

#include "Widget.h"

class Button : public Widget
{
    Sprite * m_released;
    Sprite * m_rollOver;
    Sprite * m_pressed;

public:
    Button(Widget * parent = 0,
           float x = 0.f,
           float y = 0.f,
           float width = 0.f,
           float height = 0.f);
    ~Button();

protected:
    void draw();
    void update();
};
