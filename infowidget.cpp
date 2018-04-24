#include "infowidget.hpp"
#include <QHBoxLayout>
#include <QLabel>
#include <QDebug>

InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    _timer(new QTimer(this))
{
    move(600, 200);
    _createLayout();
    _initConnetions();
}

void InfoWidget::showEvent(QShowEvent *event)
{
   _timer->start(3000);
}

void InfoWidget::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVBoxLayout* rightLayout = new QVBoxLayout;

    auto addLabel = [this, leftLayout, rightLayout](QString text, QString val){
        QLabel* nameLabel = new QLabel(this);
        QLabel* valLabel = new QLabel(this);
        nameLabel->setText(text);
        valLabel->setText(val);
        leftLayout->addWidget(nameLabel);
        rightLayout->addWidget(valLabel);
    };

    addLabel("Отправляемый и получаемый пакеты", "Ctrl + 1");
    addLabel("Отладка движетелей", "Ctrl + 2");
    addLabel("Информация о джойстике", "Ctrl + 3");
    addLabel("Настройка джойстика", "Ctrl + 7");
    addLabel("Настройка камер", "Ctrl + 8");
    addLabel("Загрузка прошивки ардуино", "Ctrl + 9");
    addLabel("Закрыть приложение", "Ctrl + Q");

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    setLayout(mainLayout);
}

void InfoWidget::_initConnetions()
{
    connect(_timer, &QTimer::timeout, [this](){
       this->hide();
       _timer->stop();
    });
}
