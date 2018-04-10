#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _settings(new QSettings(".ini", QSettings::IniFormat)),
    _joystickMediator(new JoystickMediator(_settings, this)),
    _dataStore(new DataStore(this)),
    _timerWidget(new TimerWidget(this)),
    _camerasControlWidget(new CamerasControlWidget(_settings, this))
{
    _createLayout();
    _initConnections();
    _createIcons();
}

void MainWidget::ShowJoysticConfig()
{
    _joystickMediator->showDialog();
}

void MainWidget::ShowCamerasConfig()
{
    _camerasControlWidget->showConfigDialog();
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

void MainWidget::_createIcons()
{
    _joysticIcon = new QLabel(this);
    _joysticIcon->setFixedSize(36, 36);
    _joysticIcon->move(50, 643);
    _joysticIcon->setStyleSheet(QString("background-image: url(joystick.png);"));
    _joysticIcon->setVisible(false);

    _ethernetIcon = new QLabel(this);
    _ethernetIcon->setFixedSize(31, 31);
    _ethernetIcon->move(99, 647);
    _ethernetIcon->setStyleSheet(QString("background-image: url(ethernet.png);"));
    _ethernetIcon->setVisible(false);
}

void MainWidget::_initConnections()
{
    connect(_joystickMediator, &JoystickMediator::AxisXChange, _dataStore, &DataStore::SetAxisX);
    connect(_joystickMediator, &JoystickMediator::AxisYChange, _dataStore, &DataStore::SetAxisY);
    connect(_joystickMediator, &JoystickMediator::AxisZChange, _dataStore, &DataStore::SetAxisZ);
    connect(_joystickMediator, &JoystickMediator::AxisWChange, _dataStore, &DataStore::SetAxisW);
    connect(_joystickMediator, &JoystickMediator::ManClose, _dataStore, &DataStore::SetManClose);
    connect(_joystickMediator, &JoystickMediator::ManOpen, _dataStore, &DataStore::SetManOpen);
    connect(_joystickMediator, &JoystickMediator::ManRotateLeft, _dataStore, &DataStore::SetManRotateLLeft);
    connect(_joystickMediator, &JoystickMediator::ManRotateRight, _dataStore, &DataStore::SetManRotateRigth);

    connect(_joystickMediator, &JoystickMediator::JoystickConnect, [this](){_joysticIcon->setVisible(true);});
    connect(_joystickMediator, &JoystickMediator::JoystickDisconnect, [this](){_joysticIcon->setVisible(false);});
    connect(_dataStore, &DataStore::tcpConnect, [this](){_ethernetIcon->setVisible(true);});
    connect(_dataStore, &DataStore::tcpDisconnect, [this](){_ethernetIcon->setVisible(false);});
}

