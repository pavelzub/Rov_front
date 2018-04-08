#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "mainwidget.hpp"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void _createMenu();

    const int WINDOWHEIGTH = 720;
    const int WINDOWWIDTH = 1280;

    MainWidget* _mainWidget;
};

#endif // MAINWINDOW_HPP
