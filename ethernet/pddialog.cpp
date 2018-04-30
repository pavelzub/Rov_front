#include "pddialog.hpp"

#include <QDoubleValidator>
#include <QHBoxLayout>

PdDialog::PdDialog(rov_types::rov_enable_pd* rovEnablePd, rov_types::rov_pd *rovPd, QWidget* parent):
    QDialog(parent),
    _sendBtn(new QPushButton(this)),
    _updateBtn(new QPushButton(this))
{
    _rovEnablePd = rovEnablePd;
    _rovPd = rovPd;
    _createLayout();
    _initConnections();
    UpdatePd();
}

void PdDialog::UpdatePd()
{
    _vals[0]->setText(QString::number(_rovPd->yaw_p));
    _vals[1]->setText(QString::number(_rovPd->yaw_d));
    _vals[2]->setText(QString::number(_rovPd->depth_p));
    _vals[3]->setText(QString::number(_rovPd->depth_d));
    _vals[4]->setText(QString::number(_rovPd->roll_p));
    _vals[5]->setText(QString::number(_rovPd->roll_d));
    _vals[6]->setText(QString::number(_rovPd->roll_to_set));
    _vals[7]->setText(QString::number(_rovPd->pitch_p));
    _vals[8]->setText(QString::number(_rovPd->pitch_d));
    _vals[9]->setText(QString::number(_rovPd->pitch_to_set));

    for (int i = 0; i < 2; i++)
        _names[i]->setStyleSheet(_rovEnablePd->yaw_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 2; i < 4; i++)
        _names[i]->setStyleSheet(_rovEnablePd->depth_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 4; i < 7; i++)
        _names[i]->setStyleSheet(_rovEnablePd->roll_pd < 1 ? "color : red;" : "color : green;");
    for (int i = 7; i < 10; i++)
        _names[i]->setStyleSheet(_rovEnablePd->pitch_pd < 1 ? "color : red;" : "color : green;");
}

void PdDialog::showEvent(QShowEvent *event)
{
    _updateData();
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
        _vals.back()->setValidator(new QDoubleValidator(0, 100000, 400, this));
        _vals.back()->setEnabled(false);
        _needUpdate.back()->setChecked(false);
//        _needUpdate.back()->setStyleSheet("background:transparent;border:0");

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

    if (_needUpdate[0]->isChecked()) package.yaw_p = _vals[0]->text().toFloat();
    if (_needUpdate[1]->isChecked()) package.yaw_d = _vals[1]->text().toFloat();
    if (_needUpdate[2]->isChecked()) package.depth_p = _vals[2]->text().toFloat();
    if (_needUpdate[3]->isChecked()) package.depth_d = _vals[3]->text().toFloat();
    if (_needUpdate[4]->isChecked()) package.roll_p = _vals[4]->text().toFloat();
    if (_needUpdate[5]->isChecked()) package.roll_d = _vals[5]->text().toFloat();
    if (_needUpdate[6]->isChecked()) package.roll_to_set = _vals[6]->text().toFloat();
    if (_needUpdate[7]->isChecked()) package.pitch_p = _vals[7]->text().toFloat();
    if (_needUpdate[8]->isChecked()) package.pitch_d = _vals[8]->text().toFloat();
    if (_needUpdate[9]->isChecked()) package.pitch_to_set = _vals[9]->text().toFloat();

    emit PdChange(package);
}

void PdDialog::_updateData()
{
    rov_types::rov_pd package;
    emit PdChange(package);
}
