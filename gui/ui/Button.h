#pragma once

#include "Widget.h"

#include <ClanLib/Display/Window/input_event.h>
#include <ClanLib/Display/Window/input_state.h>
#include <ClanLib/Core/Signals/slot.h>

class Button : public Widget
{
    Sprite * m_released;
    Sprite * m_rollOver;
    Sprite * m_pressed;
    CL_Slot slotUp, slotDown;

public:
    Button(Widget * parent = 0,
           float x = 0.f,
           float y = 0.f,
           float width = 0.f,
           float height = 0.f);
    ~Button();

    void setWidth(float width);

    enum ButtonState
    {
        Released,
        RollOver,
        Pressed
    } state;

protected:
    void draw();
    void update();
    void onEvent(const CL_InputEvent & event, const CL_InputState &);
};
