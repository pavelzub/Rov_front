#include "mainwidget.hpp" 
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QKeyEvent>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
    _settings(new Settings(".ini", QSettings::IniFormat)),
    _joystickMediator(new JoystickMediator(_settings, this)),
    _dataStore(new DataStore(_settings, this)),
    _timerWidget(new TimerWidget(this)),
    _camerasControlWidget(new CamerasControlWidget(_settings, this)),
    _joystickDebugDialog(new JoystickDebugDialog(_joystickMediator, this)),
    _sensorWidget(new SensorsWidget(this)),
    _infoWidget(new InfoWidget(this)),
    _depthDialog(new DepthDialog)
{
    _createLayout();
    _initConnections();
    _createIcons();
    setFocusPolicy(Qt::ClickFocus);
    setFixedSize(1280, 720);
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
    switch (event->key()) {
        case Qt::Key_Control:
            _infoWidget->show();
            break;
        case Qt::Key_Z:
            _dataStore->SetTwisting_motors(0, 1);
            break;
        case Qt::Key_X:
            _dataStore->SetTwisting_motors(0, -1);
            break;
        case Qt::Key_C:
            _dataStore->SetTwisting_motors(1, -1);
            break;
        case Qt::Key_V:
            _dataStore->SetTwisting_motors(1, 1);
            break;
        case Qt::Key_B:
            _dataStore->SetTwisting_motors(2, 1);
            break;
        case Qt::Key_N:
            _dataStore->SetTwisting_motors(2, -1);
            break;
        case Qt::Key_M:
            _dataStore->SetTwisting_motors(3, -1);
            break;
        case Qt::Key_Comma:
            _dataStore->SetTwisting_motors(3, 1);
            break;
        case Qt::Key_Y:
            emit EnableReg(0);
            break;
        case Qt::Key_D:
            emit EnableReg(1);
            break;
        case Qt::Key_R:
            emit EnableReg(2);
            break;
        case Qt::Key_P:
            emit EnableReg(3);
            break;
        case Qt::Key_Q:
            _dataStore->DisablePID();
            break;
        case Qt::Key_Plus:
            _dataStore->SetFlashLightPowerUp();
            break;
        case Qt::Key_Minus:
            _dataStore->SetFlashLightPowerDown();
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
        case Qt::Key_Plus:
            _dataStore->SetFlashLightPowerSave();
            break;
        case Qt::Key_Minus:
            _dataStore->SetFlashLightPowerSave();
            break;
    }
}

void MainWidget::_createLayout()
{
    _infoWidget->hide();
}

void MainWidget::_createIcons()
{
    _joysticIcon = new QLabel(this);
    _joysticIcon->setFixedSize(36, 36);
    _joysticIcon->move(50, 643);
    _joysticIcon->setStyleSheet("background-image: url(images/icons/joystick.png);");
    _joysticIcon->setVisible(false);

    _ethernetIcon = new QLabel(this);
    _ethernetIcon->setFixedSize(31, 31);
    _ethernetIcon->move(99, 647);
    _ethernetIcon->setStyleSheet("background-image: url(images/icons/ethernet.png);");
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
    connect(_joystickMediator, &JoystickMediator::MainCameraRotateRight, _dataStore, &DataStore::SetMainCameraRotateRight);
    connect(_joystickMediator, &JoystickMediator::MainCameraRotateLeft, _dataStore, &DataStore::SetMainCameraRotateLeft);
    connect(_joystickMediator, &JoystickMediator::SubCameraRotateRight, _dataStore, &DataStore::SetSubCameraRotateRight);
    connect(_joystickMediator, &JoystickMediator::SubCameraRotateLeft, _dataStore, &DataStore::SetSubCameraRotateLeft);
    connect(_joystickMediator, &JoystickMediator::MagnetOn, _dataStore, &DataStore::SetMagnetOn);
    connect(_joystickMediator, &JoystickMediator::MagnetOff, _dataStore, &DataStore::SetMagnetOff);
    connect(_joystickMediator, &JoystickMediator::AcousticOn, _dataStore, &DataStore::SetAcousticOn);
    connect(_joystickMediator, &JoystickMediator::AcousticOff, _dataStore, &DataStore::SetAcousticOff);
    connect(_joystickMediator, &JoystickMediator::PowerChange, _dataStore, &DataStore::SetPower);
    connect(_joystickMediator, &JoystickMediator::SaltoChange, _dataStore, &DataStore::SetSalto);
    connect(_joystickMediator, &JoystickMediator::BochkaChange, _dataStore, &DataStore::SetBochka);
    connect(_joystickMediator, &JoystickMediator::SecondManOpen, _dataStore, &DataStore::SetSecondManOpen);
    connect(_joystickMediator, &JoystickMediator::SecondManClose, _dataStore, &DataStore::SetSecondManClose);

    connect(_joystickMediator, &JoystickMediator::JoystickConnect, [this](){_joysticIcon->setVisible(true);});
    connect(_joystickMediator, &JoystickMediator::JoystickDisconnect, [this](){_joysticIcon->setVisible(false);});

    connect(_camerasControlWidget, &CamerasControlWidget::changeMainCameraIndex, _dataStore, &DataStore::SetMainCameraIndex);

    connect(_dataStore, &DataStore::tcpConnect, [this](){_ethernetIcon->setVisible(true);});
    connect(_dataStore, &DataStore::tcpDisconnect, [this](){_ethernetIcon->setVisible(false);});
    connect(_dataStore, &DataStore::telimetryUpdate, _sensorWidget, &SensorsWidget::TelimetryChange);
    connect(_dataStore, &DataStore::enablePdUpdate, _sensorWidget, &SensorsWidget::RegChange);
    connect(this, &MainWidget::EnableReg, _dataStore, &DataStore::SetEnablePd);

    connect(_dataStore, &DataStore::telimetryUpdate, _depthDialog, &DepthDialog::setDepth);
    connect(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_4), this), &QShortcut::activated, [this](){_depthDialog->show();});
}

