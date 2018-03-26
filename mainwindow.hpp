#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "gamepadmanager.hpp"
#include "mainwidget.hpp"
#include "calculationwindow.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void test();

    CalculationWindow* _calcWindow;
    MainWidget* _mainWidget;
    MyGamepadManager *_gamepadManager;
};

#endif // MAINWINDOW_HPP
