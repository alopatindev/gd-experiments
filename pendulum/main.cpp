#include <ClanLib/core.h>
#include <ClanLib/application.h>
#include <ClanLib/display.h>
#include <ClanLib/gl1.h>
#include <ClanLib/Display/Window/keys.h>
#include <ClanLib/swrender.h>

#include "mainwindow.h"

class App
{
public:
    static int main(const std::vector<CL_String> &args)
    {
        CL_SetupCore setup_core;
        CL_SetupDisplay setup_display;
        CL_SetupGL1 setup_opengl1;
        CL_SetupSWRender setup_swrender;

        MainWindow w;
        w.run();

        return 0;
    }
};

CL_ClanApplication app(&App::main);
