#include "packagedebugdialog.hpp"
#include <QVBoxLayout>
#include <QLabel>

PackageDebugDialog::PackageDebugDialog(rov_types::rov_debug *rovDebug, QWidget *parent):
    QDialog (parent)
{
    _rovDebug = rovDebug;
    _createLayout();
}

void PackageDebugDialog::Update()
{
    for (int i = 0; i < 8; i++)
        _power[i]->setValue(_rovDebug->thruster_power[i]);
}

void PackageDebugDialog::closeEvent(QCloseEvent *event)
{
    emit visibleChange(false);
}

void PackageDebugDialog::showEvent(QShowEvent *event)
{
    emit visibleChange(true);
}

void PackageDebugDialog::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* nameLayout = new QVBoxLayout;
    QVBoxLayout* sliderLayout = new QVBoxLayout;
    QVBoxLayout* valLayout = new QVBoxLayout;

    for (int i = 0; i < 8; i++){
        QLabel* name = new  QLabel(this);
        name->setText("Motor " + QString::number(i) + ":");
        nameLayout->addWidget(name);

        _power[i] = new QSlider(this);
        _power[i]->setOrientation(Qt::Orientation::Horizontal);
        _power[i]->setMinimum(-100);
        _power[i]->setMaximum(100);
        sliderLayout->addWidget(_power[i]);

        QLabel* valLabel = new QLabel(this);
        valLabel->setText("0");
        valLabel->setFixedWidth(30);
        valLabel->setAlignment(Qt::AlignCenter);
        valLayout->addWidget(valLabel);

        connect(_power[i], &QSlider::valueChanged, [this, valLabel, i](int val){
           _rovDebug->thruster_power[i] = static_cast<int8_t>(val);
           valLabel->setText(QString::number(val));
        });
    }

    mainLayout->addLayout(nameLayout);
    mainLayout->addLayout(sliderLayout);
    mainLayout->addLayout(valLayout);
    setLayout(mainLayout);
}
