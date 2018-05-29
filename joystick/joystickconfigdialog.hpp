#ifndef JOYSTICKCONFIGDIALOG_HPP
#define JOYSTICKCONFIGDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QList>
#include <QCheckBox>

#include "settings.hpp"
#include "joystickmanager.hpp"
#include "clickablelabel.hpp"

void _camera1RotateRight(int val, int step);
void _camera1RotateLeft(int val, int step);
void _camera2RotateRight(int val, int step);
void _camera2RotateLeft(int val, int step);
void _magnetOn(int val, int step);
void _magnetOff(int val, int step);
void _acousticOn(int val, int step);
void _acousticOff(int val, int step);

static const QList<QString> availableSlots = {"_manRotateRight", "_manRotateLeft", "_manOpen", "_manClose", "_axisXChange", "_axisYChange", "_axisZChange", "_axisWChange",
                                       "_mainCameraRotateRight", "_mainCameraRotateLeft", "_subCameraRotateRight", "_subCameraRotateLeft", "_magnetOn", "_magnetOff", "_acousticOn", "_acousticOff", "_powerChange",
                                       "_saltoChange", "_bochkaChange", "_secondManOpen", "_secondManClose"};
static const QList<QString> rusNames = {"Ман. вправо", "Ман. влево ", "Ман. закрыть", "Ман. открыть", "Ось Х", "Ось Y", "Ось Z", "Ось W",
                                       "Гланая камера вправо", "Главная камера влево", "Побочная камера вправо", "Побочная камера влево", "Включить магнит", "Выключить магнит", "Включить аккустику", "Выключить аккустику",
                                       "Изменить мощность", "Сальто", "Бочка", "Открыть побочный манипулятор", "Закрыть побочный манипулятор"};
static const QList<QString> defaultSignals = {"ChangeAxis_0", "ChangeButton_1", "ChangeButton_2", "ChangeButton_3", "ChangeButton_4", "ChangeButton_5", "ChangeButton_6", "ChangeButton_7",
                                             "ChangeAxis_0", "ChangeButton_1", "ChangeButton_2", "ChangeButton_3", "ChangeButton_4", "ChangeButton_5", "ChangeButton_6", "ChangeButton_7", "ChangeButton_7",
                                             "ChangeButton_7", "ChangeButton_7", "ChangeButton_7", "ChangeButton_7"};

class JoystickConfigDialog : public QDialog
{
    Q_OBJECT
public:
    JoystickConfigDialog(JoystickManager* joysticManager, Settings* settings, QWidget* parent = nullptr);

private slots:
    void _changeConfig(int val, int step);

protected:
    void closeEvent(QCloseEvent * event);

private:
    void _createLayouts();
    void _initConnections();
    void _selectLabel(int i);
    void _checkCheckBox(int i, bool isCheck);

    int _selectIndex = -1;
    JoystickManager* _joysticManager;
    Settings* _settings;
    QList<ClickableLabel*> _buttons;
    QList<QCheckBox*> _checkBoxs;
};

#endif // JOYSTICKCONFIGDIALOG_HPP
