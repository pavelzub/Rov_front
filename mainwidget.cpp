#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _settings(new QSettings(".ini", QSettings::IniFormat)),
    _joystickMediator(new JoystickMediator(_settings, this)),
    _dataStore(this),
//    _timerWidget(new TimerWidget(this)),
    _camerasControlWidget(new CamerasControlWidget(this))
{
    _createLayout();
    _initConnections();
}

void MainWidget::ShowJoysticConfig()
{
    _joystickMediator->ShowDialog();
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
    connect(_joystickMediator, &JoystickMediator::AxisXChange, &_dataStore, &DataStore::SetAxisX);
    connect(_joystickMediator, &JoystickMediator::AxisYChange, &_dataStore, &DataStore::SetAxisY);
    connect(_joystickMediator, &JoystickMediator::AxisZChange, &_dataStore, &DataStore::SetAxisZ);
    connect(_joystickMediator, &JoystickMediator::AxisWChange, &_dataStore, &DataStore::SetAxisW);
    connect(_joystickMediator, &JoystickMediator::ManClose, &_dataStore, &DataStore::SetManClose);
    connect(_joystickMediator, &JoystickMediator::ManOpen, &_dataStore, &DataStore::SetManOpen);
    connect(_joystickMediator, &JoystickMediator::ManRotateLeft, &_dataStore, &DataStore::SetManRotateLLeft);
    connect(_joystickMediator, &JoystickMediator::ManRotateRight, &_dataStore, &DataStore::SetManRotateRigth);
}

