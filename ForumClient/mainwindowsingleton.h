#ifndef MAINWINDOWSINGLETON_H
#define MAINWINDOWSINGLETON_H

#include "mainwindow.h"

class MainWindowSingleton
{
private:
    static MainWindowSingleton *instanta;

    MainWindow w;

    MainWindowSingleton();
    ~MainWindowSingleton() {};
    MainWindowSingleton(const MainWindowSingleton& obj) {};

public:
    static MainWindowSingleton& getInstance();
    static void destroyInstance();

};

#endif // MAINWINDOWSINGLETON_H
