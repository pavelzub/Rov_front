#include "depthdialog.hpp"

#include <QGridLayout>
#include <QPushButton>

DepthDialog::DepthDialog()
{
    _createLayout();
}

void DepthDialog::setDepth(float yaw, float pitch, float roll, float depth)
{
    _depth ->setText(QString::number(depth));
}

void DepthDialog::_createLayout()
{
    auto layout = new QGridLayout;

    _depth = new QLabel(this);
    QLabel* val2 = new QLabel(this);
    QLabel* val3 = new QLabel(this);
    QLabel* val4 = new QLabel(this);
    _depth->setStyleSheet("{ font-size: 20px }");
    val2->setStyleSheet("{ font-size: 20px }");
    val3->setStyleSheet("{ font-size: 20px }");
    val4->setStyleSheet("{ font-size: 20px }");

    layout->addWidget(_depth, 0, 1);
    layout->addWidget(val2, 1, 1);
    layout->addWidget(val3, 2, 1);
    layout->addWidget(val4, 3, 1);

    QLabel* depth1 = new QLabel(this);
    depth1->setText("Current depth: ");

    QPushButton* depth2 = new QPushButton(this);
    depth2->setText("Bottom depth: ");
    connect(depth2, &QPushButton::pressed, [this, val2, val3, val4](){
        val2->setText(_depth->text());
        val4->setText(QString::number(val2->text().toDouble() - val3->text().toDouble() + 2.5));
    });
//    depth2->setFixedSize(100,20);

    QPushButton* depth3 = new QPushButton(this);
    depth3->setText("ADV depth: ");
    connect(depth3, &QPushButton::pressed, [this, val2, val3, val4](){
        val3->setText(_depth->text());
        val4->setText(QString::number(val2->text().toDouble() - val3->text().toDouble() + 2.5));
    });
//    depth3->setFixedSize(100,20);

    QLabel* depth4 = new QLabel(this);
    depth4->setText("Distane: ");

    depth1->setStyleSheet("{ font-size: 20px }");
    depth2->setStyleSheet("{ font-size: 20px }");
    depth3->setStyleSheet("{ font-size: 20px }");
    depth4->setStyleSheet("{ font-size: 20px }");

    layout->addWidget(depth1, 0, 0);
    layout->addWidget(depth2, 1, 0);
    layout->addWidget(depth3, 2, 0);
    layout->addWidget(depth4, 3, 0);

    setLayout(layout);
}
