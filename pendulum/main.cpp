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

        bool fullscreen = false;
        for (auto it = args.begin(); it != args.end(); ++it) {
            if (*it == CL_String("--fullscreen")) {
                fullscreen = true;
                continue;
            }
        }

        MainWindow w;
        w.run(640, 480, fullscreen);

        return 0;
    }
};

CL_ClanApplication app(&App::main);
