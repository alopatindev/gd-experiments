#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <ClanLib/Sound/soundbuffer.h>
#include <ClanLib/Sound/soundbuffer_session.h>
#include <ClanLib/Sound/setupsound.h>
#include <ClanLib/Sound/soundoutput.h>
//#include <ClanLib/Sound/SoundFilters/fadefilter.h>
#include <ClanLib/Vorbis/setupvorbis.h>

class MainWindow
{
    bool quit;
    int windowWidth;
    int windowHeight;

public:
    MainWindow();
    virtual ~MainWindow();

    void run(int width, int height, bool fullscreen);
    void onClose();
};

#endif
