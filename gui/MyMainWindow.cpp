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
    okay->onPress.connect(this, &MyMainWindow::on_Button_press);
    addWidget(okay);
}

void MyMainWindow::on_Button_press()
{
    cout << "onPress" << endl;
}
