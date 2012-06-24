#ifndef PENDULUM_H
#define PENDULUM_H

#include <ClanLib/display.h>
#include <cmath>
#include <ClanLib/Display/2D/sprite.h> 
           
const float MAX_ANGLE = M_PI / 2;

class Pendulum
{
    CL_GraphicContext *gc;
    CL_InputContext *ic;
    uint timer;
    float startAngle;
    float currentAngle;
    float step;
    float lastMaxY;
    bool mouseDown;
    CL_Sprite arrow;

    CL_Slot slotMouseDown, slotMouseUp;
    void onMouseDown(const CL_InputEvent &, const CL_InputState &);
    void onMouseUp(const CL_InputEvent &, const CL_InputState &);

public:
    Pendulum(CL_GraphicContext & gc, CL_InputContext & ic,
             CL_ResourceManager & resources);
    virtual ~Pendulum();
    void update(int dt);
    static float y(float x);
};

static const float MAX_FUNC_Y = Pendulum::y(0.);

#endif
