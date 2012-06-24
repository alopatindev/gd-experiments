#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ClanLib/Sound/soundbuffer.h>
#include <ClanLib/Sound/soundbuffer_session.h>
#include <ClanLib/Sound/setupsound.h>
#include <ClanLib/Sound/soundoutput.h>
//#include <ClanLib/Sound/SoundFilters/fadefilter.h>
#include <ClanLib/Vorbis/setupvorbis.h>

const int WINDOW_WIDTH = 640;
const int WINDOW_HEIGHT = 480;

class MainWindow
{
    bool quit;

public:
    MainWindow();
    virtual ~MainWindow();

    void run();
    void onClose();
};

#endif
