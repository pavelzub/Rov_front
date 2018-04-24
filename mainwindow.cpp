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
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q), this), &QShortcut::activated, [this](){exit(0);});

    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_7), this), &QShortcut::activated, _mainWidget, &MainWidget::ShowJoysticConfig);
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_8), this), &QShortcut::activated, _mainWidget, &MainWidget::ShowCamerasConfig);
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_3), this), &QShortcut::activated, _mainWidget, &MainWidget::ShowJoysticDebug);
}
