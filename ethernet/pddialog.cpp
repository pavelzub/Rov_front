#include "pddialog.hpp"

#include <QDoubleValidator>
#include <QHBoxLayout>
#include <QDebug>

PdDialog::PdDialog(QWidget* parent):
    QDialog(parent),
    _sendBtn(new QPushButton(this)),
    _updateBtn(new QPushButton(this))
{
    _createLayout();
    _initConnections();
}

void PdDialog::UpdatePd(rov_types::rov_pd pd)
{
    _vals[0]->setText(QString::number(pd.yaw_p).replace(".", ","));
    _vals[1]->setText(QString::number(pd.yaw_i).replace(".", ","));
    _vals[2]->setText(QString::number(pd.yaw_d).replace(".", ","));
    _vals[3]->setText(QString::number(pd.depth_p).replace(".", ","));
    _vals[4]->setText(QString::number(pd.depth_i).replace(".", ","));
    _vals[5]->setText(QString::number(pd.depth_d).replace(".", ","));
    _vals[6]->setText(QString::number(pd.roll_p).replace(".", ","));
    _vals[7]->setText(QString::number(pd.roll_i).replace(".", ","));
    _vals[8]->setText(QString::number(pd.roll_d).replace(".", ","));
    _vals[9]->setText(QString::number(pd.roll_to_set).replace(".", ","));
    _vals[10]->setText(QString::number(pd.pitch_p).replace(".", ","));
    _vals[11]->setText(QString::number(pd.pitch_i).replace(".", ","));
    _vals[12]->setText(QString::number(pd.pitch_d).replace(".", ","));
    _vals[13]->setText(QString::number(pd.pitch_to_set).replace(".", ","));
}

void PdDialog::UpdateEnablePd(rov_types::rov_enable_pd enablePd)
{
    for (int i = 0; i < 3; i++)
        _names[i]->setStyleSheet(enablePd.yaw_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 3; i < 6; i++)
        _names[i]->setStyleSheet(enablePd.depth_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 6; i < 10; i++)
        _names[i]->setStyleSheet(enablePd.roll_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 10; i < 14; i++)
        _names[i]->setStyleSheet(enablePd.pitch_pd < 1 ? "color : red;" : "color : green;");
}

void PdDialog::showEvent(QShowEvent *event)
{
    emit NeedUpdate();
}

void PdDialog::_createLayout()
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* infoLayout = new QHBoxLayout;
    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    QVBoxLayout* namesLayout = new QVBoxLayout;
    QVBoxLayout* valsLayout = new QVBoxLayout;
    QVBoxLayout* flagsLayout = new QVBoxLayout;


    for (int i = 0; i < NAMES.size(); i++){
        _names.push_back(new QLabel(this));
        _vals.push_back(new QLineEdit(this));
        _needUpdate.push_back(new QCheckBox(this));

        _names.back()->setText(NAMES[i] + ": ");
        _vals.back()->setValidator(new QDoubleValidator(-10000, 10000, 400, this));
        _vals.back()->setEnabled(false);
        _needUpdate.back()->setChecked(false);

        namesLayout->addWidget(_names.back());
        valsLayout->addWidget(_vals.back());
        flagsLayout->addWidget(_needUpdate.back());
    }

    _sendBtn->setText("Сохранить");
    _updateBtn->setText("Обновить");

    infoLayout->addLayout(namesLayout);
    infoLayout->addLayout(valsLayout);
    infoLayout->addLayout(flagsLayout);
    buttonsLayout->addWidget(_sendBtn);
    buttonsLayout->addWidget(_updateBtn);
    layout->addLayout(infoLayout);
    layout->addLayout(buttonsLayout);
    setLayout(layout);
}

void PdDialog::_initConnections()
{
    connect(_sendBtn, &QPushButton::clicked, this, &PdDialog::_sendData);
    connect(_updateBtn, &QPushButton::clicked, this, &PdDialog::_updateData);

    for (int i = 0; i < NAMES.size(); i++)
        connect(_needUpdate[i], &QCheckBox::clicked, [this, i](){
            _vals[i]->setEnabled(_needUpdate[i]->isChecked());
    });
}

void PdDialog::_sendData()
{
    rov_types::rov_pd package;

    if (_needUpdate[0]->isChecked()) package.yaw_p = _vals[0]->text().replace(",", ".").toFloat();
    if (_needUpdate[1]->isChecked()) package.yaw_i = _vals[1]->text().replace(",", ".").toFloat();
    if (_needUpdate[2]->isChecked()) package.yaw_d = _vals[2]->text().replace(",", ".").toFloat();
    if (_needUpdate[3]->isChecked()) package.depth_p = _vals[3]->text().replace(",", ".").toFloat();
    if (_needUpdate[4]->isChecked()) package.depth_i = _vals[4]->text().replace(",", ".").toFloat();
    if (_needUpdate[5]->isChecked()) package.depth_d = _vals[5]->text().replace(",", ".").toFloat();
    if (_needUpdate[6]->isChecked()) package.roll_p = _vals[6]->text().replace(",", ".").toFloat();
    if (_needUpdate[7]->isChecked()) package.roll_i = _vals[7]->text().replace(",", ".").toFloat();
    if (_needUpdate[8]->isChecked()) package.roll_d = _vals[8]->text().replace(",", ".").toFloat();
    if (_needUpdate[9]->isChecked()) package.roll_to_set = _vals[9]->text().replace(",", ".").toFloat();
    if (_needUpdate[10]->isChecked()) package.pitch_p = _vals[10]->text().replace(",", ".").toFloat();
    if (_needUpdate[11]->isChecked()) package.pitch_i = _vals[11]->text().replace(",", ".").toFloat();
    if (_needUpdate[12]->isChecked()) package.pitch_d = _vals[12]->text().replace(",", ".").toFloat();
    if (_needUpdate[13]->isChecked()) package.pitch_to_set = _vals[13]->text().replace(",", ".").toFloat();

    emit PdChange(package);
}

void PdDialog::_updateData()
{
    emit NeedUpdate();
}
