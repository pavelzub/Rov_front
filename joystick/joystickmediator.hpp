#ifndef JOYSTICKMEDIATOR_HPP
#define JOYSTICKMEDIATOR_HPP

#include <QObject>
#include "joystick/joystickmanager.hpp"

class JoystickMediator : public QObject
{
    Q_OBJECT
public:
    explicit JoystickMediator(QObject *parent = nullptr);

private:
    JoystickManager _gamepadManager;
};

#endif // JOYSTICKMEDIATOR_HPP
