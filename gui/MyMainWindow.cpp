#include "MyMainWindow.h"
#include <iostream>

using namespace std;

MyMainWindow::MyMainWindow()
    : MainWindow()
{
}

MyMainWindow::~MyMainWindow()
{
}

void MyMainWindow::setup()
{
    okay = new Button(this, 50.f, 80.f, 100.0f, 40.f);
    okay->onDoubleClick.connect(this, &MyMainWindow::on_Button_doubleClick);
    addWidget(okay);
}

void MyMainWindow::on_Button_doubleClick()
{
    cout << "onDoubleClick" << endl;
}
