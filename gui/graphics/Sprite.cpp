#include "Sprite.h"
#include "../libs/DeviceScreen.h"
#include "../libs/ResourceManager.h"

Sprite::Sprite(const CL_StringRef &fullname)
    : CL_Sprite(*GC, fullname, &RC)
{
}

void Sprite::setWidth(float width)
{
    Rect::setWidth(width);

    float w, h;
    get_scale(w, h);

    // 1.  - get_width()
    //     - width

    set_scale(width / get_width(), h);
}
