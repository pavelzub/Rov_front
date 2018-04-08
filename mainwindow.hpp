#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

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
    void _createMenu();

    const int WINDOWHEIGTH = 720;
    const int WINDOWWIDTH = 1280;

    CalculationWindow* _calcWindow;
    MainWidget* _mainWidget;
};

#endif // MAINWINDOW_HPP
