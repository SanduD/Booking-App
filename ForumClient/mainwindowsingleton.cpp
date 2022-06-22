#include "mainwindowsingleton.h"

MainWindowSingleton* MainWindowSingleton::instanta = nullptr;

MainWindowSingleton::MainWindowSingleton()
{
    w.setWindowTitle("Forum POO");
    w.setWindowFlags(Qt::WindowMinimizeButtonHint | Qt::WindowCloseButtonHint); //
    w.showMaximized();
}

MainWindowSingleton& MainWindowSingleton::getInstance()
{
    if (instanta == nullptr)
    {
        MainWindowSingleton::instanta = new MainWindowSingleton();
    }
    return *MainWindowSingleton::instanta;
}

void MainWindowSingleton::destroyInstance()
{
    if (MainWindowSingleton::instanta != nullptr)
    {
        delete MainWindowSingleton::instanta;
        MainWindowSingleton::instanta = nullptr;
    }
}
