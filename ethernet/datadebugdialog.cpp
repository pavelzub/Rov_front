#include "datadebugdialog.hpp"
#include <QVBoxLayout>
#include <iostream>

DataDebugDialog::DataDebugDialog(rov_types::rov_telimetry *telimetry, rov_types::rov_control *control, QWidget *parent):
    QDialog (parent)
{
    _control = control;
    _telimetry = telimetry;
    _createLayout();
    Update();
}

void DataDebugDialog::Update()
{
    _telimetryVals[0]->setText(QString::number(static_cast<double>(_telimetry->yaw)));
    _telimetryVals[1]->setText(QString::number(static_cast<double>(_telimetry->pitch)));
    _telimetryVals[2]->setText(QString::number(static_cast<double>(_telimetry->roll)));
    _telimetryVals[3]->setText(QString::number(static_cast<double>(_telimetry->depth)));
    _telimetryVals[4]->setText(QString::number(_telimetry->mega_communication));
    _telimetryVals[5]->setText(QString::number(_telimetry->mini_communication));
    _telimetryVals[6]->setText(QString::number(_telimetry->esp_communication));
    _telimetryVals[7]->setText(QString::number(_telimetry->esp_state));
    _telimetryVals[8]->setText(QString::number(_telimetry->manipulator_rotated));
    _telimetryVals[9]->setText(QString::number(_telimetry->manipulator_opened_closed));
    _telimetryVals[10]->setText(QString::number(_telimetry->camera_rotate[0]));
    _telimetryVals[11]->setText(QString::number(_telimetry->camera_rotate[1]));
    _telimetryVals[12]->setText(QString::number(_telimetry->magnet));
    _telimetryVals[13]->setText(QString::number(_telimetry->acoustic));

    _controlVals[0]->setText(QString::number(_control->axis_x));
    _controlVals[1]->setText(QString::number(_control->axis_y));
    _controlVals[2]->setText(QString::number(_control->axis_z));
    _controlVals[3]->setText(QString::number(_control->axis_w));
    _controlVals[4]->setText(QString::number(_control->manipulator_rotate));
    _controlVals[5]->setText(QString::number(_control->manipulator_open_close));
    _controlVals[6]->setText(QString::number(_control->camera_rotate[0]));
    _controlVals[7]->setText(QString::number(_control->camera_rotate[1]));
    _controlVals[8]->setText(QString::number(_control->magnet));
    _controlVals[9]->setText(QString::number(_control->acoustic));
    _controlVals[10]->setText(QString::number(_control->twisting_motors[0]));
    _controlVals[11]->setText(QString::number(_control->twisting_motors[1]));
    _controlVals[12]->setText(QString::number(_control->twisting_motors[2]));
    _controlVals[13]->setText(QString::number(_control->twisting_motors[3]));
    _controlVals[14]->setText(QString::number(_control->secondary_maninpulator));
}

void DataDebugDialog::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    auto addLayouts = [this, mainLayout](QList<QLabel*>* labels, QList<QString> names){
        QVBoxLayout* nameLayout = new QVBoxLayout;
        QVBoxLayout* valLayout = new QVBoxLayout;

        for (int i = 0; i < names.size(); i++){
            QLabel* name = new QLabel(this);
            name->setText(names[i] + ":");
            labels->push_back(new QLabel(this));
            labels->back()->setFixedWidth(40);
            nameLayout->addWidget(name);
            valLayout->addWidget(labels->back());
        }

        mainLayout->addLayout(nameLayout);
        mainLayout->addLayout(valLayout);
    };

    const QList<QString> telimetryNames = {"yaw", "pitch", "roll", "depth", "mega_communication", "mini_communication", "esp_communication", "esp_state",
                                      "manipulator_rotated", "manipulator_opened_closed", "camera_rotate0", "camera_rotate1", "magnet", "acoustic"};
    const QList<QString> controlNames = {"axis_x", "axis_y", "axis_z", "axis_w", "manipulator_rotate", "manipulator_open_close", "camera_rotate0", "camera_rotate1",
                                        "magnet", "acoustic", "twisting_motors0", "twisting_motors1", "twisting_motors2", "twisting_motors3", "subman"};

    addLayouts(&_telimetryVals, telimetryNames);
    addLayouts(&_controlVals, controlNames);
    setLayout(mainLayout);
}
