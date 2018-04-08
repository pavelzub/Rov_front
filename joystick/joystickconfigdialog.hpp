#ifndef JOYSTICKCONFIGDIALOG_HPP
#define JOYSTICKCONFIGDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QLabel>
#include <QList>
#include <QCheckBox>

#include "joystickmanager.hpp"
#include "clickablelabel.hpp"

static const QList<QString> availableSlots = {"_manRotateRight", "_manRotateLeft", "_manOpen", "_manClose",
                                       "_axisXChange", "_axisYChange", "_axisZChange", "_axisWChange"};
static const QList<QString> rusNames = {"Ман. в право", "Ман в лево ", "Ман. открыть", "Ман. закрыть",
                                       "Ось Х", "Ось Y", "Ось Z", "Ось W"};
static const QList<QString> defaultSignals = {"ChangeAxis_0", "ChangeButton_1", "ChangeButton_2", "ChangeButton_3",
                                       "ChangeButton_4", "ChangeButton_5", "ChangeButton_6", "ChangeButton_7"};

class JoystickConfigDialog : public QDialog
{
    Q_OBJECT
public:
    JoystickConfigDialog(JoystickManager* joysticManager, QSettings* settings, QWidget* parent = nullptr);

signals:
    void configUpdate();

private slots:
    void _changeConfig(int val, int step);

private:
    void _createLayouts();
    void _initConnections();
    void _selectLabel(int i);
    void _checkCheckBox(int i, bool isCheck);

    int _selectIndex = -1;
    JoystickManager* _joysticManager;
    QSettings* _settings;
    QList<ClickableLabel*> _buttons;
    QList<QCheckBox*> _checkBoxs;
};

#endif // JOYSTICKCONFIGDIALOG_HPP
