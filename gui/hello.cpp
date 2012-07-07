#include "MyMainWindow.h"
#include "libs/ResourceManager.h"

#include <clocale>
#include <ClanLib/core.h>
#include <ClanLib/application.h>

class App
{
public:
    static int main(const std::vector<CL_String> & args)
    {
        std::setlocale(LC_ALL, "");
        //try {
            ResourceManager::getInstance() = CL_ResourceManager("resources.xml");

            MyMainWindow mainWindow;
            String title("Hello!");
            mainWindow.setTitle(title);
            mainWindow.setSize(640, 480);
            //mainWindow.setFullscreen();
            mainWindow.run();
        /*} catch (CL_Exception & exception) {
            CL_ConsoleWindow console("Console", 80, 160);
            CL_Console::write_line("Error: " +
                                   exception.get_message_and_stack_trace());
            console.display_close_message();
        }*/

        return 0;
    }
};

CL_ClanApplication app(&App::main);
