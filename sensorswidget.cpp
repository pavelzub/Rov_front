#include "sensorswidget.hpp"
#include <QPainter>

SensorsWidget::SensorsWidget(QWidget *parent) : QWidget(parent)
{
   setFixedSize(390, 720);
   _initPixmaps();
   _createVals();
   _createLabels();
   TelimetryChange(0, 0, 0);
}

void SensorsWidget::TelimetryChange(float yaw, float pitch, float roll)
{
    QPixmap pixmap = _createPixmap(yaw, 0);
    _labels[0]->setPixmap(pixmap);
    pixmap = _createPixmap(pitch, 1);
    _labels[1]->setPixmap(pixmap);
    pixmap = _createPixmap(roll, 2);
    _labels[2]->setPixmap(pixmap);
}

void SensorsWidget::_createLabels()
{
    for (int i = 0; i < 3; i++){
        _labels[i] = new QLabel(this);
        _labels[i]->setFixedSize(103, 103);
        _labels[i]->setAlignment(Qt::AlignCenter);
    }

    _labels[0]->move(18, 176);
    _labels[1]->move(148, 176);
    _labels[2]->move(278, 176);
}

void SensorsWidget::_initPixmaps()
{
    _pixmaps[0] = QPixmap("yaw.png");
    _pixmaps[1] = QPixmap("pitch.png");
    _pixmaps[2] = QPixmap("roll.png");
}

void SensorsWidget::_createVals()
{
    for(int i = 0; i < 3; i++){
        _vals[i] = new QLabel(this);
        _vals[i]->setFont(QFont("DS-Digital", 20));
        _vals[i]->setAlignment(Qt::AlignCenter);
        _vals[i]->setFixedWidth(103);
    }
    _vals[0]->move(18, 286);
    _vals[1]->move(148, 286);
    _vals[2]->move(278, 286);
}

QPixmap SensorsWidget::_createPixmap(float angle, int index)
{
    QPixmap pixmap(103, 103);
    QTransform tran;
    tran = tran.rotate(angle);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.drawPixmap(QRect(18, 18, 67, 67), _pixmaps[index]);
    painter.end();
    pixmap = pixmap.transformed(tran);


    QString fonttemplate = tr("<font color='White'>%1</font>");
    _vals[index]->setText(fonttemplate.arg(angle));
    return  pixmap;
}
