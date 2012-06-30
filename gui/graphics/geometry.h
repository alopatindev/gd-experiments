#pragma once

#include <vector>

class Rect
{
    float m_x, m_y;
    float m_width, m_height;

public:
    Rect(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f);
    ~Rect();
    void setCoords(float x0, float y0, float x1, float y1);
    void setCoords(float x0, float y0);
    void setX(float x);
    void setY(float y);
    void setWidth(float width);
    void setHeight(float height);
    void setSize(float width, float height);
    void setX1(float x1);
    void setY1(float y1);
    float x();
    float y();
    float x1();
    float y1();
    float width();
    float height();
    bool collides(Rect & rect);
    bool collides(Rect * rect);
};

class Point2
{
    float m_x, m_y;

public:
    Point2(float x = 0.f, float y = 0.f);
    ~Point2();
    float x();
    float y();
    void setCoords(float x, float y);
    void setX(float x);
    void setY(float y);
};

typedef std::vector<Point2> Vec2;
