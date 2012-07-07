#include "DeviceScreen.h"
#include <iostream>

ScreenClass::ScreenClass()
{
    m_setupCore = new CL_SetupCore;
    m_setupDisplay = new CL_SetupDisplay;
    m_setupOpenGl1 = new CL_SetupGL1;
    m_setupSwrender = new CL_SetupSWRender;
    m_ic = 0;
    m_gc = 0;
    m_dt = 0;
}

ScreenClass::~ScreenClass()
{
    delete m_setupCore;
    delete m_setupDisplay;
    delete m_setupOpenGl1;
    delete m_setupSwrender;
}

void ScreenClass::setGraphicContext(CL_GraphicContext * gc)
{
    m_gc = gc;
}

void ScreenClass::setInputContext(CL_InputContext * ic)
{
    m_ic = ic;
}

CL_GraphicContext * ScreenClass::getGraphicContext()
{
    return m_gc;
}

CL_InputContext * ScreenClass::getInputContext()
{
    return m_ic;
}

void ScreenClass::setDt(int dt)
{
    m_dt = dt;
}

int ScreenClass::getDt()
{
    return m_dt;
}
