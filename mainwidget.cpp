#include "mainwidget.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    createLayout();
    disableAll();
}

void MainWidget::setAxisText(int index, QString text)
{
    m_axis[index]->setText(text);
}

void MainWidget::setButtonsText(int index, QString text)
{
    m_buttons[index]->setText(text);
}

void MainWidget::disableAll()
{
    for (int i = 0; i < 9; i++){
        m_axis[i]->setEnabled(false);
        m_buttons[i]->setEnabled(false);
    }
}

void MainWidget::enableAll()
{
    for (int i = 0; i < 9; i++){
        m_axis[i]->setEnabled(true);
        m_buttons[i]->setEnabled(true);
    }
}

void MainWidget::createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* axisLayout = new QHBoxLayout;
    for (int i = 0; i < 9; i++)
    {
        m_axis[i] = new QTextEdit(this);
        axisLayout->addWidget(m_axis[i]);
    }

    QHBoxLayout* buttonsLayout = new QHBoxLayout;
    for (int i = 0; i < 9; i++)
    {
        m_buttons[i] = new QTextEdit(this);
        buttonsLayout->addWidget(m_buttons[i]);
    }

    mainLayout->addLayout(axisLayout);
    mainLayout->addLayout(buttonsLayout);

    this->setLayout(mainLayout);
}
