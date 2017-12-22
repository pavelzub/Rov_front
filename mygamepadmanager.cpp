#include "mygamepadmanager.hpp"
#include <QMetaObject>
#include <iostream>

MyGamepadManager::MyGamepadManager(QObject *parent)
    : QObject(parent),
      _timer(new QTimer(this))
{
    initializeTimer();
    initializeConnetions();
}

void MyGamepadManager::setConnectionStatus(bool isConnect)
{
    if (!_isGamepadConnect && isConnect)
        emit GamepadConnect();
    if (_isGamepadConnect && !isConnect)
        emit GamepadDisconnect();

    _isGamepadConnect = isConnect;
}

void MyGamepadManager::refreshGamepadInfo()
{
    SDL_Quit();
    SDL_Init(SDL_INIT_JOYSTICK);

    if (SDL_NumJoysticks() == 0)
    {
        setConnectionStatus(false);
        return;
    };

    SDL_Joystick* joystik = SDL_JoystickOpen(0);

    SDL_JoystickUpdate();

    for (int i = 0; i < AXISCOUNT; i++)
    {
        double axisVal = (double)SDL_JoystickGetAxis(joystik, i) / (double)SHRT_MAX;
        if (_axis[i] != axisVal)
        {
            _axis[i] = axisVal;
            const char* signalName = QString("ChangeAxis_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(double, axisVal));
            std::cout << QString("ChangeAxis_" + QString::number(i)).toStdString() << ": " << axisVal << std::endl;
        }

    }

    for (int i = 0; i < BUTTONSCOUNT; i++)
    {
        double ButtonVal = (double)SDL_JoystickGetButton(joystik, i);
        if (_buttons[i] != ButtonVal)
        {
            _buttons[i] = ButtonVal;
            const char* signalName = QString("ChangeButton_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(double, ButtonVal));
            std::cout << QString("ChangeButton_" + QString::number(i)).toStdString() << ": " << ButtonVal << std::endl;
        }
    }

    for (int i = 0; i < HATSCOUNT; i++)
    {
        int HatVal = SDL_JoystickGetHat(joystik, i);
        if (_hats[i] != HatVal)
        {
            _hats[i] = HatVal;
            const char* signalName = QString("ChangeHat_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(int, HatVal));
            std::cout << QString("ChangeHat_" + QString::number(i)).toStdString() << ": " << HatVal << std::endl;
        }
    }

    setConnectionStatus(true);
}

void MyGamepadManager::initializeConnetions()
{
    connect(_timer, &QTimer::timeout, this, &refreshGamepadInfo);
}

void MyGamepadManager::initializeTimer()
{
//     | SDL_INIT_GAMECONTROLLER
    if (SDL_Init(SDL_INIT_JOYSTICK) != 0)
    {
        std::cout << "SDL init error!" << std::endl;
        return;
    }
    _timer->start(20);
}
