#include "serveripdialog.hpp"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

ServerIpDialog::ServerIpDialog(Settings* settings, QWidget *parent):
    QDialog (parent)
{
    _settings = settings;
    _createLayout();
}

void ServerIpDialog::_createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QHBoxLayout* hLayout = new QHBoxLayout;
    QLabel* label = new QLabel(this);
    label->setText("Адрес сервера: ");

    QString url = _settings->value("SERVER/server_url", "192.168.88.251").toString();
    _serverAdress = new QLineEdit(this);
    _serverAdress->setInputMask("000.000.000.000");
    _serverAdress->setText(url);

    hLayout->addWidget(label);
    hLayout->addWidget(_serverAdress);
    mainLayout->addLayout(hLayout);

    QPushButton* btn = new QPushButton(this);
    btn->setText("OK");
    connect(btn, &QPushButton::pressed, this, &ServerIpDialog::_btnPress);

    mainLayout->addWidget(btn);
    setLayout(mainLayout);
}

void ServerIpDialog::_btnPress()
{
    _settings->setValue("SERVER/server_url", _serverAdress->text());

    _settings->serverIpNeedUpdate();
    hide();
}
