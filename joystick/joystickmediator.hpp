#ifndef JOYSTICKMEDIATOR_HPP
#define JOYSTICKMEDIATOR_HPP

#include <QObject>
#include <QSettings>
#include <QMap>

#include "joystick/joystickmanager.hpp"

class JoystickMediator : public QObject
{
    Q_OBJECT
    typedef void(*f)(int val);

public:
    explicit JoystickMediator(QSettings* settings, QObject *parent = nullptr);
    const QList<QString> availableSlots = {"_manRotateRight", "_manRotateLeft", "_manOpen", "_manClose",
                                           "_axisXChange", "_axisYChange", "_axisZChange", "_axisWChange"};
    const QList<QString> defaultSignals = {"ChangeAxis_0", "ChangeButton_1", "ChangeButton_2", "ChangeButton_3",
                                           "ChangeButton_4", "ChangeButton_5", "ChangeButton_6", "ChangeButton_7"};

signals:
    void ManRotateRight(int);
    void ManRotateLeft(int);
    void ManOpen(int);
    void ManClose(int);
    void AxisXChange(int);
    void AxisYChange(int);
    void AxisZChange(int);
    void AxisWChange(int);

private slots:
    void _manRotateRight(int val);
    void _manRotateLeft(int val);
    void _manOpen(int val);
    void _manClose(int val);
    void _axisXChange(int val);
    void _axisYChange(int val);
    void _axisZChange(int val);
    void _axisWChange(int val);

private:
    void _changeConnection(QString signal, QString slot, bool connect = true);
    void _loadSettings();

    QMap<QString, bool> _inverts;
    QSettings* _settings;
    JoystickManager* _joysticManager;
};

#endif // JOYSTICKMEDIATOR_HPP
