#pragma once

#include "Widget.h"
#include "../graphics/Sprite.h"

class MainWindow : public Widget
{
    bool m_fullscreen;
    Sprite * m_sprite;

public:
    MainWindow();
    void run();
    virtual void setup();

    void setFullscreen(bool fullscreen = true);
    void setSprite(Sprite * sprite);

protected:
    virtual void draw();
};
