#include "Button.h"
#include "../libs/ResourceManager.h"
#include "../libs/DeviceScreen.h"

#include <iostream>
using namespace std;

Button::Button(Widget * parent, float x, float y, float width, float height)
    : Widget(parent, x, y, width, height)
{
    state = Released;

    m_released = new Sprite("menu/button/released");
    m_rollOver = new Sprite("menu/button/roll_over");
    m_pressed = new Sprite("menu/button/pressed");

    slotDown = MOUSE.sig_key_down().connect(this, &Button::onEvent);
    slotUp = MOUSE.sig_key_up().connect(this, &Button::onEvent);
}

Button::~Button()
{
    delete m_released;
    delete m_rollOver;
    delete m_pressed;
}

void Button::draw()
{
    //Widget::draw();

    if (!visible())
        return;

    switch (state) {
    case Released:
        m_released->draw(*GC, x(), y());
        m_released->update();
        break;
    case RollOver:
        m_rollOver->draw(*GC, x(), y());
        m_rollOver->update();
        break;
    case Pressed:
        m_pressed->draw(*GC, x(), y());
        m_pressed->update();
        break;
    }
    
    CL_Draw::box(*GC, x(), y(), width(), height(), CL_Colorf::red);
}

void Button::update()
{
    if (state != Pressed) {
        if (this->collides(MOUSE.get_x(), MOUSE.get_y()))
            state = RollOver;
        else
            state = Released;
    }

    //if (this->collides(DeviceScreen::getInstance()))
    //    draw();

    m_released->setSize(width(), height());
    m_rollOver->setSize(width(), height());
    m_pressed->setSize(width(), height());

    Widget::update();
}

void Button::onEvent(const CL_InputEvent & event, const CL_InputState &)
{
    switch (event.type) {
    case CL_InputEvent::pressed:
        if (this->collides(MOUSE.get_x(), MOUSE.get_y()))
            state = Pressed;
        break;
    case CL_InputEvent::released:
        state = Released;
        break;
    default:
        break;
    }
}
