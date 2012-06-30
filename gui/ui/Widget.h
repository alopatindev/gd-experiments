#pragma once

#include <set>
#include "../graphics/geometry.h"
#include "../graphics/Texture.h"
#include "../graphics/Sprite.h"
#include "../libs/String.h"

class Widget : public Rect
{
    Widget * m_parent;

    std::set<Widget *> m_children;

    enum LayoutType {
        Float,
        Horizontal,
        Vertical
    } m_layout;

    float m_hspacing;
    float m_vspacing;

    bool m_autoResize;

    bool m_visible;
    int m_alpha;

    Sprite * m_mouseCursor;

    Rect m_viewPort;

    Texture * m_texture;

    String m_title;

public:
    Widget(Widget * parent = 0,
           float x = 0.f,
           float y = 0.f,
           float width = 0.f,
           float height = 0.f);
    virtual ~Widget();

    void addWidget(Widget * widget, bool pushBack = true);

    void setLayout(LayoutType layout);

    // only for non-float layout
    void setSpacing(float hspacing, float vspacing);
    void setHSpacing(float hspacing);
    void setVSpacing(float vspacing);

    // only for Float layout
    void setAutoResize(bool autoResize);

    void setTitle(String & title);
    void setTitle(String * title);
    String & getTitle();

    void setVisible(bool visible);

    // 0xFF means fully visible
    void setAlpha(int alpha);

    void setMouseCursor(Sprite * mouseCursor);

    void setViewPort(float x, float y, float width, float height);
    void setViewPort(Rect & rect);

    void setTexture(Texture * texture);

protected:
    virtual void draw();
    void update();
};
