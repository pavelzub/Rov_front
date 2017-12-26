#include "gamepadmanager.hpp"
#include <QMetaObject>
#include <iostream>

MyGamepadManager::MyGamepadManager(QObject *parent)
    : QObject(parent),
      m_timer(new QTimer(this))
{
    initializeTimer();
    initializeConnetions();
}

void MyGamepadManager::setConnectionStatus(bool isConnect)
{
    if (!m_isGamepadConnect && isConnect)
        emit GamepadConnect();
    if (m_isGamepadConnect && !isConnect)
        emit GamepadDisconnect();

    m_isGamepadConnect = isConnect;
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

    refreshAxisInfo(joystik);
    refreshButtonInfo(joystik);
    refreshHatInfo(joystik);

    setConnectionStatus(true);
}

void MyGamepadManager::refreshAxisInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumAxes(joystik); i++)
    {
        double axisVal = (double)SDL_JoystickGetAxis(joystik, i) / (double)SHRT_MAX;
        if (m_axis[i] != axisVal)
        {
            m_axis[i] = axisVal;
            const char* signalName = QString("ChangeAxis_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(double, axisVal));
            std::cout << QString("ChangeAxis_" + QString::number(i)).toStdString() << ": " << axisVal << std::endl;
        }
    }
}

void MyGamepadManager::refreshButtonInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumButtons(joystik); i++)
    {
        double buttonVal = (double)SDL_JoystickGetButton(joystik, i);
        if (m_buttons[i] != buttonVal)
        {
            m_buttons[i] = buttonVal;
            const char* signalName = QString("ChangeButton_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(double, buttonVal));
            std::cout << QString("ChangeButton_" + QString::number(i)).toStdString() << ": " << buttonVal << std::endl;
        }
    }
}

void MyGamepadManager::refreshHatInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumHats(joystik); i++)
    {
        int hatVal = SDL_JoystickGetHat(joystik, i);
        if (m_hats[i] != hatVal)
        {
            m_hats[i] = hatVal;
            const char* signalName = QString("ChangeHat_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(int, hatVal));
            std::cout << QString("ChangeHat_" + QString::number(i)).toStdString() << ": " << hatVal << std::endl;
        }
    }
}

void MyGamepadManager::initializeConnetions()
{
    connect(m_timer, &QTimer::timeout, this, &refreshGamepadInfo);
}

void MyGamepadManager::initializeTimer()
{
    m_timer->start(20);
}
