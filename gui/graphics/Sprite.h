#pragma once

#include <ClanLib/Display/2D/sprite.h>
#include "geometry.h"

class Sprite : public CL_Sprite, public Rect
{
    float lastWidth;
    float lastHeight;

public:
    Sprite(const CL_StringRef &fullname);
    virtual void update();
};
