#include "joystickconfigdialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMetaMethod>
#include <QMetaObject>
#include <iostream>

JoystickConfigDialog::JoystickConfigDialog(JoystickManager *joysticManager, QSettings *settings, QWidget *parent):
    QDialog(parent)
{
    _joysticManager = joysticManager;
    _settings = settings;
    _createLayouts();
    _initConnections();

}

void JoystickConfigDialog::_changeConfig(int val, int step)
{
    if (abs(step) < 2000 || _selectIndex == -1) return;
    QMetaMethod metaMethod = sender()->metaObject()->method(senderSignalIndex());
    QString name = metaMethod.name();

    _settings->beginGroup("JOYSTICK");
    _settings->setValue(availableSlots[_selectIndex], name);
    _settings->endGroup();

    _buttons[_selectIndex]->setText(name);
    _selectLabel(-1);

    emit configUpdate();
}

void JoystickConfigDialog::_createLayouts()
{
    QHBoxLayout* mainLayout(new QHBoxLayout(this));
    QVBoxLayout* nameLayout(new QVBoxLayout);
    QVBoxLayout* valLayout(new QVBoxLayout);
    QVBoxLayout* invertLayout(new QVBoxLayout);

    _settings->beginGroup("JOYSTICK");
    for (int i = 0; i < availableSlots.size(); i++){
        QLabel* name = new QLabel(this);
        _buttons.push_back(new ClickableLabel(this));
        _checkBoxs.push_back(new QCheckBox(this));

        name->setText(rusNames[i] + ": ");
        QString signalName = _settings->value(availableSlots[i], defaultSignals[i]).toString();
        _buttons.back()->setText(signalName);
        bool ischeck = _settings->value(availableSlots[i] + "Invert", 0).toInt();
        _checkBoxs.back()->setChecked(ischeck);

        nameLayout->addWidget(name);
        valLayout->addWidget(_buttons[i]);
        invertLayout->addWidget(_checkBoxs[i]);
    }
    _settings->endGroup();

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(valLayout);
    mainLayout->addLayout(invertLayout);
    setLayout(mainLayout);

}

void JoystickConfigDialog::_initConnections()
{
    for (int i = 0; i < availableSlots.size(); i++){
        connect(_buttons[i], &ClickableLabel::clicked, [this, i](){
            _selectLabel(i);
        });
        connect(_checkBoxs[i], &QCheckBox::stateChanged, [this, i](int state){
            _checkCheckBox(i, state == Qt::CheckState::Checked);
        });
    }

    int index = this->metaObject()->indexOfSlot(QMetaObject::normalizedSignature(qPrintable("_changeConfig(int, int)")));
    QMetaMethod slot = this->metaObject()->method(index);

    for (int i = 0; i < 20; i++){
        index = _joysticManager->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable("ChangeButton_" + QString::number(i) + "(int, int)")));
        QMetaMethod signal = _joysticManager->metaObject()->method(index);
        connect(_joysticManager, signal, this, slot);
    }
    for (int i = 0; i < 10; i++){
        index = _joysticManager->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable("ChangeAxis_" + QString::number(i) + "(int, int)")));
        QMetaMethod signal = _joysticManager->metaObject()->method(index);
        connect(_joysticManager, signal, this, slot);
    }
    for (int i = 0; i < 2; i++){
        index = _joysticManager->metaObject()->indexOfSignal(QMetaObject::normalizedSignature(qPrintable("ChangeHat_" + QString::number(i) + "(int, int)")));
        QMetaMethod signal = _joysticManager->metaObject()->method(index);
        connect(_joysticManager, signal, this, slot);
    }
}

void JoystickConfigDialog::_selectLabel(int i)
{
    //#353535
    for (auto &i : _buttons)
         i->setStyleSheet("background-color: transparent;");
    _selectIndex = i;
    if (i != -1) _buttons[i]->setStyleSheet("background-color:red;");
}

void JoystickConfigDialog::_checkCheckBox(int i, bool isCheck)
{
    _settings->beginGroup("JOYSTICK");
    _settings->setValue(availableSlots[i] + "Invert" , isCheck);
    _settings->endGroup();

    emit configUpdate();
}
