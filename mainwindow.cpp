#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>
#include <QMenuBar>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _mainWidget(new MainWidget(this)),
      _background(new QPixmap("background.jpg"))
{
    setCentralWidget(_mainWidget);
    setFixedSize(WINDOWWIDTH, WINDOWHEIGTH);

    _createMenu();
}


void MainWindow::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    QPainter painter(this);
    painter.drawPixmap(0, 0, width(), height(), *_background);
    painter.end();
}

MainWindow::~MainWindow()
{
}

void MainWindow::_createMenu()
{
    QAction* ExitAct = new QAction("Джостик", this);
    QAction* djAct = new QAction("Джостик", this);
    QAction* camAct = new QAction("Камеры", this);
    ExitAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    djAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_J));
    camAct->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_K));
    addAction(ExitAct);
    addAction(djAct);
    addAction(camAct);
//    auto fileMenu = menuBar()->addMenu("Настроки");
//    fileMenu->addAction(djAct);
//    fileMenu->addAction(camAct);

    connect(ExitAct, &QAction::triggered, [this](){exit(0);});
    connect(djAct, &QAction::triggered, _mainWidget, &MainWidget::ShowJoysticConfig);
    connect(camAct, &QAction::triggered, _mainWidget, &MainWidget::ShowCamerasConfig);
}
