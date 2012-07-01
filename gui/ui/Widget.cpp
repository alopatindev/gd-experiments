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

    m_sprite = 0;
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

void Widget::setSprite(Sprite * sprite)
{
    m_sprite = sprite;
}

void Widget::setWidth(float width)
{
    Rect::setWidth(width);
    if (m_sprite)
        m_sprite->setWidth(width);
}

void Widget::draw()
{
    if (!m_visible)
        return;

    CL_GraphicContext * gc = DeviceScreen::getInstance().getGraphicContext();
    if (!gc)
        return;

    if (!m_sprite)
        CL_Draw::fill(*gc, 0.f, 0.f, width(), height(), CL_Colorf::grey);
    else
        m_sprite->draw(*gc, x(), y());
}

void Widget::update()
{
    if (this->collides(DeviceScreen::getInstance()))
        draw();

    for (auto child = m_children.begin(); child != m_children.end(); ++child)
        (*child)->update();
}
