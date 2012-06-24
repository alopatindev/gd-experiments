#include "pendulum.h"
#include "mainwindow.h"
//#include <iostream>

using namespace std;

Pendulum::Pendulum(CL_GraphicContext & gc,
                   CL_InputContext & ic,
                   CL_ResourceManager & resources)
{
    timer = 0;
    startAngle = 0.0f;
    currentAngle = 0.0f;
    step = 0.0f;
    this->gc = &gc;
    this->ic = &ic;
    lastMaxY = 0.0f;

    mouseDown = false;
    slotMouseDown = ic.get_mouse().sig_key_down().connect(
        this, &Pendulum::onMouseDown);
    slotMouseUp = ic.get_mouse().sig_key_up().connect(
        this, &Pendulum::onMouseUp);

    arrow = CL_Sprite(gc, "arrow", &resources);
    arrow.set_frame_offset(0,
        CL_Point(0, arrow.get_height() / 2 - arrow.get_height() / 10));
}

Pendulum::~Pendulum()
{
}

float Pendulum::y(float x)
{
    return (exp(-0.1f * x) * cos(2.0f * x));
}

void Pendulum::update(int dt)
{
    uint currentTime = CL_System::get_time();

    if (mouseDown) {
        step = 0.0f;

        /* proportion:

            640 -   MAX_ANGLE*2
            320 -   MAX_ANGLE
            0   -   0
        */

        startAngle = -( (((float)ic->get_mouse().get_x() * MAX_ANGLE) /
                      (WINDOW_WIDTH / 2)) - MAX_ANGLE );

        if (startAngle < -MAX_ANGLE)
            startAngle = -MAX_ANGLE;
        else if (startAngle > MAX_ANGLE)
            startAngle = MAX_ANGLE;

        currentAngle = startAngle;
    } else if (ic->get_keyboard().get_keycode(CL_KEY_SPACE)) {
        step = 0.0f;

        startAngle = currentAngle;
        if (startAngle < MAX_ANGLE)
            startAngle += 1.0f/(10.0f * M_PI);

        currentAngle = startAngle;
    } else {
        if (startAngle != 0.0f) {
            if (currentTime - timer > dt) {
                step += 0.05f;
                timer = currentTime;
            }

            float x = step;
            float yx = y(x);

            /* proportion:
            
               maxAngle or startAngle   -   y(0.0f)
               currentAngle             -   y(current)
            */

            currentAngle = (startAngle * yx) / MAX_FUNC_Y;
            //cout << currentAngle << endl;

            if (yx > 0.0f) {
                if (yx > lastMaxY)
                    lastMaxY = yx;
                else {
                    if (lastMaxY > 0.0f && lastMaxY < 0.0001f) {
                        step = 0.0f;
                        startAngle = 0.0f;
                        currentAngle = 0.0f;
                    }
                    lastMaxY = 0.0f;
                }
            }
        }
    }

    arrow.set_angle(CL_Angle::from_radians(currentAngle));
    arrow.draw(*gc,
               gc->get_width() / 2 - arrow.get_width() / 2,
               gc->get_height() / 2 - arrow.get_height());
    arrow.update();
}

void Pendulum::onMouseDown(const CL_InputEvent &, const CL_InputState &)
{
    mouseDown = true;
}

void Pendulum::onMouseUp(const CL_InputEvent &, const CL_InputState &)
{
    mouseDown = false;
}
