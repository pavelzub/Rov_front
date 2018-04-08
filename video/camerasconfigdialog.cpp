#include "camerasconfigdialog.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QString>
#include <QPushButton>
#include <iostream>

CamerasConfigDialog::CamerasConfigDialog(QSettings* settings, QWidget *parent):
    QDialog(parent)
{
    _settings = settings;
    setMinimumWidth(300);
    _createLayout();
}

void CamerasConfigDialog::_createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    for (int i = 0; i < 2; i++){
        QHBoxLayout* hLayout = new QHBoxLayout;
        QLabel* label = new QLabel(this);
        label->setText("Udp адрес камеры №" + QString::number(i + 3));

        QString url = _settings->value("CAMERAS/cam_" + QString::number(i + 3) + "_url", "192.168.1.255:1234").toString();
        _camerasAdress.push_back(new QLineEdit(this));
        _camerasAdress.back()->setInputMask("000.000.000.000:0000");
        _camerasAdress.back()->setText(url);

        hLayout->addWidget(label);
        hLayout->addWidget(_camerasAdress[i]);
        mainLayout->addLayout(hLayout);
    }

    QPushButton* btn = new QPushButton(this);
    btn->setText("OK");
    connect(btn, &QPushButton::pressed, this, &CamerasConfigDialog::_btnPress);

    mainLayout->addWidget(btn);
    setLayout(mainLayout);
}

void CamerasConfigDialog::_btnPress()
{
    for (int i = 0; i < 2; i++){
        _settings->setValue("CAMERAS/cam_" + QString::number(i + 3) + "_url", _camerasAdress[i]->text());
    }

    emit configUpdate();
    hide();
}
