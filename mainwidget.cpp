#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _gamepadManager(this),
    _dataStore(this),
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
    connect(&_gamepadManager, &GamepadManager::ChangeAxis_0, &_dataStore, &DataStore::SetAxisX);
    connect(&_gamepadManager, &GamepadManager::ChangeAxis_1, &_dataStore, &DataStore::SetAxisY);
    connect(&_gamepadManager, &GamepadManager::ChangeAxis_2, &_dataStore, &DataStore::SetAxisZ);
    connect(&_gamepadManager, &GamepadManager::ChangeAxis_3, &_dataStore, &DataStore::SetAxisW);
}

