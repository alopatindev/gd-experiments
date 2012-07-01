#pragma once

#include <vector>

class Point2;

class Rect
{
    float m_x, m_y;
    float m_width, m_height;

public:
    Rect(float x = 0.f, float y = 0.f, float width = 0.f, float height = 0.f);
    ~Rect();
    virtual void setCoords(float x0, float y0, float x1, float y1);
    virtual void setCoords(float x0, float y0);
    virtual void setX(float x);
    virtual void setY(float y);
    virtual void setWidth(float width);
    virtual void setHeight(float height);
    virtual void setSize(float width, float height);
    virtual void setX1(float x1);
    virtual void setY1(float y1);
    float x();
    float y();
    float x1();
    float y1();
    float width();
    float height();
    bool collides(Rect & rect);
    bool collides(Rect * rect);
    bool collides(float x, float y);
    bool collides(int x, int y);
    bool collides(Point2 & point);
    bool collides(Point2 * point);
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
