#include "MainWindow.h"
#include "../libs/DeviceScreen.h"
#include <ClanLib/Core/System/keep_alive.h>

MainWindow::MainWindow()
{
    m_fullscreen = false;
    m_sprite = 0;
}

void MainWindow::setFullscreen(bool fullscreen)
{
    m_fullscreen = fullscreen;
}

void MainWindow::run()
{
    DeviceScreen::getInstance();  // initialize rendering

    CL_DisplayWindow window(getTitle(),
                            (int)width(),
                            (int)height(),
                            m_fullscreen);

    CL_Rect g = window.get_geometry();

    DeviceScreen::getInstance().setSize(g.get_width(), g.get_height());
    setSize(g.get_width(), g.get_height());
    setWidth(g.get_width());

    CL_GraphicContext gc = window.get_gc();
    CL_InputContext ic = window.get_ic();
    DeviceScreen::getInstance().setGraphicContext(&gc);
    DeviceScreen::getInstance().setInputContext(&ic);
    setup();

    /*CL_Slot slotQuit = window.sig_window_close().connect(
        this,
        &MainWindow::onClose
    );*/

    uint currentTime = 0;
    int dt = 0;
    while (true) {
        currentTime = CL_System::get_time();
        if (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE))
            break;
        update();
        window.flip(0);
        CL_KeepAlive::process();
        CL_System::sleep(1);
        dt = (int)(CL_System::get_time() - currentTime);
        DeviceScreen::getInstance().setDt(dt);
    }
}

void MainWindow::setup()
{
}

void MainWindow::draw()
{
    if (!m_sprite)
        CL_Draw::fill(*GC, 0.f, 0.f, width(), height(), CL_Colorf::grey);
    else
        m_sprite->draw(*GC, x(), y());

    Widget::draw();
}

void MainWindow::setSprite(Sprite * sprite)
{
    m_sprite = sprite;
}
