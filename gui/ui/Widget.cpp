#include "Widget.h"
#include "../libs/DeviceScreen.h"
#include <ClanLib/Display/2D/draw.h>

Widget::Widget(Widget * parent, float x, float y, float width, float height)
    : Rect(x, y, width, height)
{
    m_parent = parent;

    m_hspacing = 10.f;
    m_vspacing = 10.f;

    m_autoResize = true;

    m_visible = true;
    m_alpha = 0xFF;

    m_mouseCursor = 0;

    m_viewPort = *((Rect *)this);
    
    state = Released;
}

Widget::~Widget()
{
    for (auto child = m_children.begin(); child != m_children.end(); ++child)
        delete *child;
    m_children.clear();
}

void Widget::addWidget(Widget * widget, bool pushBack)
{
    if (pushBack)
        m_children.push_back(widget);
    else
        m_children.insert(m_children.begin(), widget);
}

void Widget::setLayout(LayoutType layout)
{
    m_layout = layout;
}

void Widget::setSpacing(float hspacing, float vspacing)
{
    m_hspacing = hspacing;
    m_vspacing = vspacing;
}

void Widget::setHSpacing(float hspacing)
{
    m_hspacing = hspacing;
}

void Widget::setVSpacing(float vspacing)
{
    m_vspacing = vspacing;
}

void Widget::setAutoResize(bool autoResize)
{
    m_autoResize = autoResize;
}

void Widget::setTitle(String & title)
{
    m_title = title;
}

void Widget::setTitle(String * title)
{
    m_title = *title;
}

String & Widget::getTitle()
{
    return m_title;
}

void Widget::setVisible(bool visible)
{
    m_visible = visible;
}

bool Widget::visible()
{
    return m_visible;
}

void Widget::setAlpha(int alpha)
{
    m_alpha = alpha;
    for (auto child = m_children.begin(); child != m_children.end(); ++child)
        (*child)->setAlpha(alpha);
}

void Widget::setMouseCursor(Sprite * mouseCursor)
{
    m_mouseCursor = mouseCursor;
}

void Widget::setViewPort(float x, float y, float width, float height)
{
    m_viewPort = Rect(x, y, width, height);
}

void Widget::setViewPort(Rect & rect)
{
    m_viewPort = rect;
}

void Widget::draw()
{
    /*if (!m_visible)
        return;

    CL_GraphicContext * gc = DeviceScreen::getInstance().getGraphicContext();
    if (!gc)
        return;*/
}

void Widget::update()
{
    if (state != Pressed) {
        if (this->collides(MOUSE.get_x(), MOUSE.get_y()))
            state = RollOver;
        else
            state = Released;
    }

    if (this->collides(DeviceScreen::getInstance()))
        draw();

    for (auto child = m_children.begin(); child != m_children.end(); ++child)
        (*child)->update();
}

void Widget::enableInputEvents()
{
    slotDown = MOUSE.sig_key_down().connect(this, &Widget::inputEvent);
    slotUp = MOUSE.sig_key_up().connect(this, &Widget::inputEvent);
}

void Widget::inputEvent(const CL_InputEvent & event, const CL_InputState &)
{
    switch (event.type) {
    case CL_InputEvent::pressed:
        if (this->collides(MOUSE.get_x(), MOUSE.get_y())) {
            state = Pressed;
            onPress.emit();
        }
        break;
    case CL_InputEvent::released:
        state = Released;
        break;
    default:
        break;
    }
}
