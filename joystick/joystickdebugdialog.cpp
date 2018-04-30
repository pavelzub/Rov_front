#include "joystickdebugdialog.hpp"

#include <QHBoxLayout>

JoystickDebugDialog::JoystickDebugDialog(JoystickMediator *joysticMediator, QWidget *parent):
    QDialog (parent)
{
    _createLayouts();
    _initConnection(joysticMediator);
}

void JoystickDebugDialog::_createLayouts()
{
    QHBoxLayout* mainLayout(new QHBoxLayout(this));
    QVBoxLayout* nameLayout(new QVBoxLayout());
    QVBoxLayout* valLayout(new QVBoxLayout());

    for (int i = 0; i < availableSlots.size(); i++){
        QLabel* name = new QLabel(this);
        _vals.push_back(new QLabel(this));
        name->setText(rusNames[i] + ": ");

        nameLayout->addWidget(name);
        valLayout->addWidget(_vals[i]);
    }

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(valLayout);
    setLayout(mainLayout);
}

void JoystickDebugDialog::_initConnection(JoystickMediator *joysticMediator)
{
    connect(joysticMediator, &JoystickMediator::ManRotateRight, [this](int val){_updateVal(0, val);});
    connect(joysticMediator, &JoystickMediator::ManRotateLeft, [this](int val){_updateVal(1, val);});
    connect(joysticMediator, &JoystickMediator::ManOpen, [this](int val){_updateVal(2, val);});
    connect(joysticMediator, &JoystickMediator::ManClose, [this](int val){_updateVal(3, val);});
    connect(joysticMediator, &JoystickMediator::AxisXChange, [this](int val){_updateVal(4, val);});
    connect(joysticMediator, &JoystickMediator::AxisYChange, [this](int val){_updateVal(5, val);});
    connect(joysticMediator, &JoystickMediator::AxisZChange, [this](int val){_updateVal(6, val);});
    connect(joysticMediator, &JoystickMediator::AxisWChange, [this](int val){_updateVal(7, val);});
    connect(joysticMediator, &JoystickMediator::MainCameraRotateRight, [this](int val){_updateVal(8, val);});
    connect(joysticMediator, &JoystickMediator::MainCameraRotateLeft, [this](int val){_updateVal(9, val);});
    connect(joysticMediator, &JoystickMediator::SubCameraRotateRight, [this](int val){_updateVal(10, val);});
    connect(joysticMediator, &JoystickMediator::SubCameraRotateLeft, [this](int val){_updateVal(11, val);});
    connect(joysticMediator, &JoystickMediator::MagnetOn, [this](int val){_updateVal(12, val);});
    connect(joysticMediator, &JoystickMediator::MagnetOff, [this](int val){_updateVal(13, val);});
    connect(joysticMediator, &JoystickMediator::AcousticOn, [this](int val){_updateVal(14, val);});
    connect(joysticMediator, &JoystickMediator::AcousticOff, [this](int val){_updateVal(15, val);});
    connect(joysticMediator, &JoystickMediator::PowerChange, [this](int val){_updateVal(16, val);});
}

void JoystickDebugDialog::_updateVal(int index, int val)
{
    _vals[index]->setText(QString::number(val));
}
