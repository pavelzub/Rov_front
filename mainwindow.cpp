#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>
#include <QMenuBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _calcWindow(new CalculationWindow),
      _mainWidget(new MainWidget(this))
{
    setCentralWidget(_mainWidget);
    setFixedSize(WINDOWWIDTH, WINDOWHEIGTH);

    _createMenu();
}

MainWindow::~MainWindow()
{
}

void MainWindow::test()
{
    _calcWindow->show();
}

void MainWindow::_createMenu()
{
    QAction* djAct = new QAction("Джостик", this);
    QAction* camAct = new QAction("Камеры", this);
    auto fileMenu = menuBar()->addMenu("Настроки");
    fileMenu->addAction(djAct);
    fileMenu->addAction(camAct);

    connect(djAct, &QAction::triggered, _mainWidget, &MainWidget::ShowJoysticConfig);
    connect(camAct, &QAction::triggered, _mainWidget, &MainWidget::ShowCamerasConfig);
}
