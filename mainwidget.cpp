#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      _timerWidget(new TimerWidget(this)),
      _camerasControlWidget(new CamerasControlWidget(this))
{
    _createLayout();
    _initConnections();
}

void MainWidget::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVBoxLayout* rigthLayout = new QVBoxLayout;

    rigthLayout->addWidget(_timerWidget);
    _timerWidget->setFixedSize(200, 200);

    leftLayout->addWidget(_camerasControlWidget);
    _camerasControlWidget->setFixedSize(500, 500);
//    camWidget->setFixedSize(500, 500);
//    leftLayout->addLayout(camerasLayout);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rigthLayout);

    this->setLayout(mainLayout);
}

void MainWidget::_initConnections()
{

}

