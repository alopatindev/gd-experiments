#include "geometry.h"

Rect::Rect(float x, float y, float width, float height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

Rect::~Rect()
{
}

void Rect::setCoords(float x0, float y0, float x1, float y1)
{
    m_x = x0;
    m_y = y0;
    m_width = x1 - m_x;
    m_height = y1 - m_y;
}

void Rect::setCoords(float x0, float y0)
{
    m_x = x0;
    m_y = y0;
}

void Rect::setX(float x)
{
    m_x = x;
}

void Rect::setY(float y)
{
    m_y = y;
}

void Rect::setWidth(float width)
{
    m_width = width;
}

void Rect::setHeight(float height)
{
    m_height = height;
}

void Rect::setSize(float width, float height)
{
    m_width = width;
    m_height = height;
}

void Rect::setX1(float x1)
{
    m_width = x1 - m_x;
}

void Rect::setY1(float y1)
{
    m_height = y1 - m_y;
}

float Rect::x()
{
    return m_x;
}

float Rect::y()
{
    return m_y;
}

float Rect::x1()
{
    return m_x + m_width;
}

float Rect::y1()
{
    return m_y + m_height;
}

float Rect::width()
{
    return m_width;
}

float Rect::height()
{
    return m_height;
}

bool Rect::collides(Rect & rect)
{
    return collides(&rect);
}

bool Rect::collides(Rect * rect)
{
    bool byX = (m_x >= rect->x() && m_x <= rect->width()) ||
               (rect->x() >= m_x && rect->x() <= m_width);

    bool byY = (m_y >= rect->y() && m_y <= rect->height()) ||
               (rect->y() >= m_y && rect->y() <= m_height);

    return byX && byY;
}

bool Rect::collides(float x, float y)
{
    bool byX = (x >= m_x && x <= m_x + m_width);
    bool byY = (y >= m_y && y <= m_y + m_height);

    return byX && byY;
}

bool Rect::collides(int x, int y)
{
    return collides((float)x, (float)y);
}

bool Rect::collides(Point2 & point)
{
    return collides(point.x(), point.y());
}

bool Rect::collides(Point2 * point)
{
    return collides(point->x(), point->y());
}

float Point2::x()
{
    return m_x;
}

float Point2::y()
{
    return m_y;
}

void Point2::setCoords(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Point2::setX(float x)
{
    m_x = x;
}

void Point2::setY(float y)
{
    m_y = y;
}
