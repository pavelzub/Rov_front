#include "joystickmediator.hpp"

#include <QMetaMethod>
#include <QDir>
#include <iostream>

JoystickMediator::JoystickMediator(QSettings *settings, QObject *parent) :
    QObject(parent),
    _joysticManager(new JoystickManager(this))
{
    _settings = settings;
    _loadSettings();
}

void JoystickMediator::_loadSettings()
{
    _settings->beginGroup("JOYSTICK");
    for (int i = 0; i < availableSlots.size(); i++){
        QString signalName = _settings->value(availableSlots[i], defaultSignals[i]).toString();
        _inverts[availableSlots[i]] = _settings->value(availableSlots[i] + "Invert", 0).toInt();
        _changeConnection(signalName, availableSlots[i]);
        std::cout << _inverts[availableSlots[i]] << std::endl;
    }
    _settings->endGroup();
}

void JoystickMediator::_manRotateRight(int val) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manRotateRight"]) val *= -1;
    emit ManRotateRight(val);
}

void JoystickMediator::_manRotateLeft(int val) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manRotateLeft"]) val *= -1;
    emit ManRotateLeft(val);
}

void JoystickMediator::_manOpen(int val) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manOpen"]) val *= -1;
    emit ManOpen(val);
}

void JoystickMediator::_manClose(int val) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manClose"]) val *= -1;
    emit ManClose(val);
}

void JoystickMediator::_axisXChange(int val) {
    if (_inverts["_axisXChange"]) val *= -1;
    emit AxisXChange(val);
}

void JoystickMediator::_axisYChange(int val) {
    if (_inverts["_axisYChange"]) val *= -1;
    emit AxisYChange(val);
}

void JoystickMediator::_axisZChange(int val) {
    if (_inverts["_axisZChange"]) val *= -1;
    emit AxisZChange(val);
}

void JoystickMediator::_axisWChange(int val) {
    if (_inverts["_axisWChange"]) val *= -1;
    emit AxisWChange(val);
}

void JoystickMediator::_changeConnection(QString signalName, QString slotName, bool needConnect)
{
    int index = _joysticManager->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(signalName + "(int)")));
    QMetaMethod signal = _joysticManager->metaObject()->method(index);

    index = this->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slotName + "(int)")));
    QMetaMethod slot = this->metaObject()->method(index);

    if (needConnect)
        connect(_joysticManager, signal, this, slot);
    else
        disconnect(_joysticManager, signal, this, slot);
}
