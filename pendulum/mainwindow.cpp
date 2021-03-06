#include "mainwindow.h"
#include "pendulum.h"

#include <ClanLib/Display/Window/display_window.h>
#include <ClanLib/display.h>
#include <ClanLib/Core/System/keep_alive.h>

MainWindow::MainWindow()
{
    quit = false;
}

MainWindow::~MainWindow()
{
}

void MainWindow::run(int width, int height, bool fullscreen)
{
    windowWidth = width;
    windowHeight = height;
    CL_DisplayWindow window("Pendulum demo",
                            windowWidth,
                            windowHeight,
                            fullscreen);
    CL_Rect g = window.get_geometry();
    windowWidth = g.get_width();
    windowHeight = g.get_height();

    CL_GraphicContext gc = window.get_gc();
    CL_InputContext ic = window.get_ic();
    CL_Slot slot_quit = window.sig_window_close().connect(
        this, &MainWindow::onClose
    );

    CL_ResourceManager resources = CL_ResourceManager("resources.xml");
    Pendulum pend(gc, ic, resources, &window);

    uint currentTime = 0;
    int dt = 0;
    while (!quit) {
        currentTime = CL_System::get_time();

        if (ic.get_keyboard().get_keycode(CL_KEY_ESCAPE))
            quit = true;

        CL_Draw::fill(gc, 0, 0, windowWidth, windowHeight, CL_Colorf::white);
        pend.update(dt);

        window.flip(0);
        CL_KeepAlive::process();
        CL_System::sleep(1);
        dt = (int)(CL_System::get_time() - currentTime);
    }
}

void MainWindow::onClose()
{
    quit = true;
}
