#include "mymainwidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

MyMainWidget::MyMainWidget(QWidget *parent)
    : QWidget(parent)
{
    createLayout();
    disableAll();
}

void MyMainWidget::setAxisText(int index, QString text)
{
    _axis[index]->setText(text);
}

void MyMainWidget::setButtonsText(int index, QString text)
{
    _buttons[index]->setText(text);
}

void MyMainWidget::disableAll()
{
    for (int i = 0; i < 9; i++){
        _axis[i]->setEnabled(false);
        _buttons[i]->setEnabled(false);
    }
}

void MyMainWidget::enableAll()
{
    for (int i = 0; i < 9; i++){
        _axis[i]->setEnabled(true);
        _buttons[i]->setEnabled(true);
    }
}

void MyMainWidget::createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* axisLayout = new QHBoxLayout;
    for (int i = 0; i < 9; i++){
        _axis[i] = new QTextEdit(this);
        axisLayout->addWidget(_axis[i]);
    }

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    for (int i = 0; i < 9; i++){
        _buttons[i] = new QTextEdit(this);
        buttonsLayout->addWidget(_buttons[i]);
    }

    mainLayout->addLayout(axisLayout);
    mainLayout->addLayout(buttonsLayout);

    this->setLayout(mainLayout);
}
