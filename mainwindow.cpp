#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _mainWidget(new MainWidget(this)),
      _gamepadManager(new MyGamepadManager(this))
{
    setCentralWidget(_mainWidget);
}

MainWindow::~MainWindow()
{

}
