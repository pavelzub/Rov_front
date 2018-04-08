#include "joystickmediator.hpp"

#include <QMetaMethod>
#include <QDir>
#include <iostream>

JoystickMediator::JoystickMediator(QSettings *settings, QWidget *parent) :
    QObject(parent),
    _joysticManager(new JoystickManager(this)),
    _configDialog(new JoystickConfigDialog(_joysticManager, settings, parent))
{
    _settings = settings;
    _updateSettings();
    _initConnections();
}

void JoystickMediator::showDialog()
{
    _configDialog->show();
}

void JoystickMediator::_updateSettings()
{
    _settings->beginGroup("JOYSTICK");

    for (int i = 0; i < availableSlots.size(); i++){
        QString signalName = _settings->value(availableSlots[i], defaultSignals[i]).toString();
        if (_connects[availableSlots[i]] != signalName){
            _changeConnection(_connects[availableSlots[i]], availableSlots[i], false);
            _connects[availableSlots[i]] = signalName;
            _changeConnection(signalName, availableSlots[i]);
        }
        _inverts[availableSlots[i]] = _settings->value(availableSlots[i] + "Invert", 0).toInt();
    }

    _settings->endGroup();
}

void JoystickMediator::_initConnections()
{
    connect(_joysticManager, &JoystickManager::JoystickConnect, [this](){emit JoystickConnect();});
    connect(_joysticManager, &JoystickManager::JoystickDisconnect, [this](){emit JoystickDisconnect();});
    connect(_configDialog, &JoystickConfigDialog::configUpdate, this, &JoystickMediator::_updateSettings);
}

void JoystickMediator::_manRotateRight(int val, int step) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manRotateRight"]) val *= -1;
    emit ManRotateRight(val);
}

void JoystickMediator::_manRotateLeft(int val, int step) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manRotateLeft"]) val *= -1;
    emit ManRotateLeft(val);
}

void JoystickMediator::_manOpen(int val, int step) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manOpen"]) val *= -1;
    emit ManOpen(val);
}

void JoystickMediator::_manClose(int val, int step) {
    val = val ? val/abs(val) : 0;
    if (_inverts["_manClose"]) val *= -1;
    emit ManClose(val);
}

void JoystickMediator::_axisXChange(int val, int step) {
    if (_inverts["_axisXChange"]) val *= -1;
    emit AxisXChange(val);
}

void JoystickMediator::_axisYChange(int val, int step) {
    if (_inverts["_axisYChange"]) val *= -1;
    emit AxisYChange(val);
}

void JoystickMediator::_axisZChange(int val, int step) {
    if (_inverts["_axisZChange"]) val *= -1;
    emit AxisZChange(val);
}

void JoystickMediator::_axisWChange(int val, int step) {
    if (_inverts["_axisWChange"]) val *= -1;
    emit AxisWChange(val);
}

void JoystickMediator::_changeConnection(QString signalName, QString slotName, bool needConnect)
{
    int index = _joysticManager->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable(signalName + "(int, int)")));
    QMetaMethod signal = _joysticManager->metaObject()->method(index);

    index = this->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable(slotName + "(int, int)")));
    QMetaMethod slot = this->metaObject()->method(index);

    if (needConnect)
        connect(_joysticManager, signal, this, slot);
    else
        disconnect(_joysticManager, signal, this, slot);
}
