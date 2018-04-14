#include "mainwidget.hpp" 
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QKeyEvent>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _settings(new QSettings(".ini", QSettings::IniFormat)),
    _joystickMediator(new JoystickMediator(_settings, this)),
    _dataStore(new DataStore(this)),
    _timerWidget(new TimerWidget(this)),
    _camerasControlWidget(new CamerasControlWidget(_settings, this)),
    _joystickDebugDialog(new JoystickDebugDialog(_joystickMediator, this)),
    _sensorWidget(new SensorsWidget(this))
{
    _createLayout();
    _initConnections();
    _createIcons();
    setFocusPolicy(Qt::ClickFocus);
}

void MainWidget::ShowJoysticConfig()
{
    _joystickMediator->showConfigDialog();
}

void MainWidget::ShowJoysticDebug()
{
    _joystickDebugDialog->show();
}

void MainWidget::ShowCamerasConfig()
{
    _camerasControlWidget->showConfigDialog();
}

void MainWidget::keyPressEvent(QKeyEvent *event)
{
    std::cout << event->key() << std::endl;
    switch (event->key()) {
        case Qt::Key_Z:
            _dataStore->SetTwisting_motors(0, 1);
            break;
        case Qt::Key_X:
            _dataStore->SetTwisting_motors(0, -1);
            break;
        case Qt::Key_C:
            _dataStore->SetTwisting_motors(1, 1);
            break;
        case Qt::Key_V:
            _dataStore->SetTwisting_motors(1, -1);
            break;
        case Qt::Key_B:
            _dataStore->SetTwisting_motors(2, 1);
            break;
        case Qt::Key_N:
            _dataStore->SetTwisting_motors(2, -1);
            break;
        case Qt::Key_M:
            _dataStore->SetTwisting_motors(3, 1);
            break;
        case Qt::Key_Comma:
            _dataStore->SetTwisting_motors(3, -1);
            break;
    }
}

void MainWidget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
        case Qt::Key_Z:
            _dataStore->SetTwisting_motors(0, 0);
            break;
        case Qt::Key_X:
            _dataStore->SetTwisting_motors(0, 0);
            break;
        case Qt::Key_C:
            _dataStore->SetTwisting_motors(1, 0);
            break;
        case Qt::Key_V:
            _dataStore->SetTwisting_motors(1, 0);
            break;
        case Qt::Key_B:
            _dataStore->SetTwisting_motors(2, 0);
            break;
        case Qt::Key_N:
            _dataStore->SetTwisting_motors(2, 0);
            break;
        case Qt::Key_M:
            _dataStore->SetTwisting_motors(3, 0);
            break;
        case Qt::Key_Comma:
            _dataStore->SetTwisting_motors(3, 0);
            break;
    }
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
    connect(_joystickMediator, &JoystickMediator::Camera1RotateRight, _dataStore, &DataStore::SetCamera1RotateRight);
    connect(_joystickMediator, &JoystickMediator::Camera1RotateLeft, _dataStore, &DataStore::SetCamera1RotateLeft);
    connect(_joystickMediator, &JoystickMediator::Camera2RotateRight, _dataStore, &DataStore::SetCamera2RotateRight);
    connect(_joystickMediator, &JoystickMediator::Camera2RotateLeft, _dataStore, &DataStore::SetCamera2RotateLeft);
    connect(_joystickMediator, &JoystickMediator::MagnetOn, _dataStore, &DataStore::SetMagnetOn);
    connect(_joystickMediator, &JoystickMediator::MagnetOff, _dataStore, &DataStore::SetMagnetOff);
    connect(_joystickMediator, &JoystickMediator::AcousticOn, _dataStore, &DataStore::SetAcousticOn);
    connect(_joystickMediator, &JoystickMediator::AcousticOff, _dataStore, &DataStore::SetAcousticOff);

    connect(_joystickMediator, &JoystickMediator::JoystickConnect, [this](){_joysticIcon->setVisible(true);});
    connect(_joystickMediator, &JoystickMediator::JoystickDisconnect, [this](){_joysticIcon->setVisible(false);});

    connect(_dataStore, &DataStore::tcpConnect, [this](){_ethernetIcon->setVisible(true);});
    connect(_dataStore, &DataStore::tcpDisconnect, [this](){_ethernetIcon->setVisible(false);});
    connect(_dataStore, &DataStore::telimetryUpdate, _sensorWidget, &SensorsWidget::TelimetryChange);
}

