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

    QAction* act = new QAction("Расчитать падение", this);
    auto fileMenu = menuBar()->addMenu("Файл");
    fileMenu->addAction(act);

    connect(act, &QAction::triggered, _mainWidget, &MainWidget::ShowJoysticConfig);
}

MainWindow::~MainWindow()
{

}

void MainWindow::test()
{
    _calcWindow->show();
}
