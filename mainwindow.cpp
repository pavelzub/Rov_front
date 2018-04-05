#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _calcWindow(new CalculationWindow),
      _mainWidget(new MainWidget(this)),
      _gamepadManager(new GamepadManager(this))
{
    setCentralWidget(_mainWidget);

    QAction* act = new QAction("Расчитать падение", this);
    auto fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(act);

    connect(act, &QAction::triggered, this, &MainWindow::test);
}

MainWindow::~MainWindow()
{

}

void MainWindow::test()
{
    _calcWindow->show();
}
