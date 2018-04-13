#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>
#include <QMenuBar>
#include <QPainter>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _mainWidget(new MainWidget(this)),
      _background(new QPixmap("background.jpg"))
{
    setCentralWidget(_mainWidget);
    setFixedSize(WINDOWWIDTH, WINDOWHEIGTH);

    _createShortcuts();
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

void MainWindow::_createShortcuts()
{
    QShortcut* ExitAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this);
    QShortcut* joystickConfigAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_J), this);
    QShortcut* joystickDebugAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_D), this);
    QShortcut* camerasConfigAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_K), this);

    connect(ExitAct, &QShortcut::activated, [this](){exit(0);});
    connect(joystickConfigAct, &QShortcut::activated, _mainWidget, &MainWidget::ShowJoysticConfig);
    connect(joystickDebugAct, &QShortcut::activated, _mainWidget, &MainWidget::ShowJoysticDebug);
    connect(camerasConfigAct, &QShortcut::activated, _mainWidget, &MainWidget::ShowCamerasConfig);
}
