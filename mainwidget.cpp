#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _joystickMediator(this),
    _dataStore(this),
//    _timerWidget(new TimerWidget(this)),
    _camerasControlWidget(new CamerasControlWidget(this))
{
    _createLayout();
    _initConnections();
}

void MainWidget::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout;

    leftLayout->addWidget(_camerasControlWidget);
    leftLayout->addStretch(1);

    mainLayout->addLayout(leftLayout);
    mainLayout->setMargin(0);

    this->setLayout(mainLayout);
}

void MainWidget::_initConnections()
{
//    connect(&_gamepadManager, &GamepadManager::ChangeAxis_0, &_dataStore, &DataStore::SetAxisX);
//    connect(&_gamepadManager, &GamepadManager::ChangeAxis_1, &_dataStore, &DataStore::SetAxisY);
//    connect(&_gamepadManager, &GamepadManager::ChangeAxis_2, &_dataStore, &DataStore::SetAxisZ);
//    connect(&_gamepadManager, &GamepadManager::ChangeAxis_3, &_dataStore, &DataStore::SetAxisW);
//    connect(&_gamepadManager, &GamepadManager::ChangeButton_0, &_dataStore, &DataStore::SetManClose);
//    connect(&_gamepadManager, &GamepadManager::ChangeButton_1, &_dataStore, &DataStore::SetManOpen);
//    connect(&_gamepadManager, &GamepadManager::ChangeButton_2, &_dataStore, &DataStore::SetManRotateLLeft);
//    connect(&_gamepadManager, &GamepadManager::ChangeButton_3, &_dataStore, &DataStore::SetManRotateRigth);
}

