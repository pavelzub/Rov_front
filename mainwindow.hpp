#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "gamepadmanager.hpp"
#include "mainwidget.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MainWidget* _mainWidget;
    MyGamepadManager *_gamepadManager;
};

#endif // MAINWINDOW_HPP
