#include "joystickmediator.hpp"

#include <QMetaMethod>
#include <QLabel>
#include <iostream>

JoystickMediator::JoystickMediator(Settings *settings, QWidget *parent) :
    QObject(parent),
    _joysticManager(new JoystickManager(this)),
    _configDialog(new JoystickConfigDialog(_joysticManager, settings, parent))
{
    _settings = settings;
    _updateSettings();
    _initConnections();
}

void JoystickMediator::showConfigDialog()
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
        _inverts[availableSlots[i]] = _settings->value(availableSlots[i] + "Invert", 0).toBool();
    }

    _settings->endGroup();
}

void JoystickMediator::_initConnections()
{
    connect(_joysticManager, &JoystickManager::JoystickConnect, [this](){emit JoystickConnect();});
    connect(_joysticManager, &JoystickManager::JoystickDisconnect, [this](){emit JoystickDisconnect();});
    connect(_settings, &Settings::joystickUpdate, this, &JoystickMediator::_updateSettings);
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
    val = val * 100 / SHRT_MAX;
    if (_inverts["_axisXChange"]) val *= -1;
    emit AxisXChange(val);
}

void JoystickMediator::_axisYChange(int val, int step) {
    val = val * 100 / SHRT_MAX;
    if (_inverts["_axisYChange"]) val *= -1;
    emit AxisYChange(val);
}

void JoystickMediator::_axisZChange(int val, int step) {
    val = val * 100 / SHRT_MAX;
    if (_inverts["_axisZChange"]) val *= -1;
    emit AxisZChange(val);
}

void JoystickMediator::_axisWChange(int val, int step) {
    val = val * 100 / SHRT_MAX;
    if (_inverts["_axisWChange"]) val *= -1;
    emit AxisWChange(val);
}

void JoystickMediator::_mainCameraRotateRight(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_mainCameraRotateRight"]) val *= -1;
    emit MainCameraRotateRight(val);
}

void JoystickMediator::_mainCameraRotateLeft(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_mainCameraRotateLeft"]) val *= -1;
    emit MainCameraRotateLeft(val);
}

void JoystickMediator::_subCameraRotateRight(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_subCameraRotateRight"]) val *= -1;
    emit SubCameraRotateRight(val);
}

void JoystickMediator::_subCameraRotateLeft(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_subCameraRotateLeft"]) val *= -1;
    emit SubCameraRotateLeft(val);
}

void JoystickMediator::_magnetOn(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_magnetOn"]) val *= -1;
    emit MagnetOn(val);
}

void JoystickMediator::_magnetOff(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_magnetOff"]) val *= -1;
    emit MagnetOff(val);
}

void JoystickMediator::_acousticOn(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_acousticOn"]) val *= -1;
    emit AcousticOn(val);
}

void JoystickMediator::_acousticOff(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_acousticOff"]) val *= -1;
    emit AcousticOff(val);
}

void JoystickMediator::_powerChange(int val, int step)
{
    if (_inverts["_powerChange"]) val *= -1;
    val = static_cast<int>(val * 100 / SHRT_MAX * 0.45 + 55);
    emit PowerChange(val);
}

void JoystickMediator::_saltoChange(int val, int step)
{
    if (_inverts["_saltoChange"]) val *= -1;
    val = val * 100 / SHRT_MAX;
    emit SaltoChange(val);
}

void JoystickMediator::_bochkaChange(int val, int step)
{
    if (_inverts["_bochkaChange"]) val *= -1;
    val = val * 100 / SHRT_MAX;
    emit BochkaChange(val);
}

void JoystickMediator::_secondManOpen(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_secondManOpen"]) val *= -1;
    emit SecondManOpen(val);
}

void JoystickMediator::_secondManClose(int val, int step)
{
    val = val ? val/abs(val) : 0;
    if (_inverts["_secondManClose"]) val *= -1;
    emit SecondManClose(val);
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
