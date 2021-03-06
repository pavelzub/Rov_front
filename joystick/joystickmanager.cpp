#include "joystickmanager.hpp"
#include <QMetaObject>
#include <iostream>
#include <QDebug>

JoystickManager::JoystickManager(QObject *parent)
    : QObject(parent),
      m_timer(new QTimer(this))
{
    initializeTimer();
    initializeConnetions();
}

void JoystickManager::setConnectionStatus(bool isConnect)
{
    if (!m_isGamepadConnect && isConnect)
        emit JoystickConnect();
    if (m_isGamepadConnect && !isConnect)
        emit JoystickDisconnect();

    m_isGamepadConnect = isConnect;
}

void JoystickManager::refreshGamepadInfo()
{
//    SDL_Quit();
//    SDL_Init(SDL_INIT_JOYSTICK);

    SDL_JoystickUpdate();
    if (SDL_NumJoysticks() == 0)
    {
        setConnectionStatus(false);
        return;
    };

    joystik = SDL_JoystickOpen(0);


    refreshAxisInfo(joystik);
    refreshButtonInfo(joystik);
    refreshHatInfo(joystik);

    setConnectionStatus(true);
}

void JoystickManager::refreshAxisInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumAxes(joystik); i++)
    {
        int axisVal = SDL_JoystickGetAxis(joystik, i);
        if (m_axis[i] != axisVal)
        {
            int step = m_axis[i] - axisVal;
            m_axis[i] = axisVal;
            const char* signalName = QString("ChangeAxis_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(int, axisVal), Q_ARG(int, step));
//            std::cout << QString("ChangeAxis_" + QString::number(i)).toStdString() << ": " << axisVal << std::endl;
        }
    }
}

void JoystickManager::refreshButtonInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumButtons(joystik); i++)
    {
        int buttonVal = SDL_JoystickGetButton(joystik, i) * SHRT_MAX;
        if (m_buttons[i] != buttonVal)
        {
            int step = m_axis[i] - buttonVal;
            m_buttons[i] = buttonVal;
            const char* signalName = QString("ChangeButton_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(int, buttonVal), Q_ARG(int, step));
//            std::cout << QString("ChangeButton_" + QString::number(i)).toStdString() << ": " << buttonVal << std::endl;
        }
    }
}

void JoystickManager::refreshHatInfo(SDL_Joystick* joystik)
{
    for (int i = 0; i < SDL_JoystickNumHats(joystik); i++)
    {
        int hatVal = SDL_JoystickGetHat(joystik, i) * SHRT_MAX / 12;
        if (m_hats[i] != hatVal)
        {
            int step = m_axis[i] - hatVal;
            m_hats[i] = hatVal;
            const char* signalName = QString("ChangeHat_" + QString::number(i)).toStdString().c_str();
            emit QMetaObject::invokeMethod(this, signalName, Qt::DirectConnection, Q_ARG(int, hatVal), Q_ARG(int, step));
//            std::cout << QString("ChangeHat_" + QString::number(i)).toStdString() << ": " << hatVal << std::endl;
        }
    }
}

void JoystickManager::initializeConnetions()
{
    connect(m_timer, &QTimer::timeout, this, &JoystickManager::refreshGamepadInfo);
}

void JoystickManager::initializeTimer()
{
    m_timer->start(20);
    SDL_Init(SDL_INIT_JOYSTICK);
}
