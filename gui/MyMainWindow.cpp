#include "MyMainWindow.h"

MyMainWindow::MyMainWindow()
    : MainWindow()
{
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::setup()
{
    okay = new Button(this, 0.f, 20.f, 100.0f, 100.f);
    okay->setWidth(300.0f);
    okay->setHeight(300.0f);
    addWidget(okay);
}
