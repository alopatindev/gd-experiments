#pragma once

#include "Singleton.h"
#include "../graphics/geometry.h"

#include <ClanLib/display.h>
//#include <ClanLib/gl.h>
#include <ClanLib/gl1.h>
#include <ClanLib/Display/Window/keys.h>
#include <ClanLib/swrender.h>
#include <ClanLib/Core/System/setup_core.h>

#include <ClanLib/Display/Render/graphic_context.h>
#include <ClanLib/Display/Window/input_context.h>

class ScreenClass : public Rect
{
    CL_SetupCore * m_setupCore;
    CL_SetupDisplay * m_setupDisplay;
    CL_SetupGL1 * m_setupOpenGl1;
    CL_SetupSWRender * m_setupSwrender;
    CL_GraphicContext * m_gc;
    CL_InputContext * m_ic;

public:
    ScreenClass();
    ~ScreenClass();
    void setGraphicContext(CL_GraphicContext * gc);
    void setInputContext(CL_InputContext * ic);
    CL_GraphicContext * getGraphicContext();
    CL_InputContext * getInputContext();
};

typedef Singleton<ScreenClass> DeviceScreen;
