#include "sensorswidget.hpp"
#include <QPainter>
#include <QDebug>

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

void SensorsWidget::RegChange(rov_types::rov_enable_pd enable_pd)
{
    _texts[0]->setVisible(enable_pd.yaw_pd == 1);
    _texts[1]->setVisible(enable_pd.pitch_pd == 1);
    _texts[2]->setVisible(enable_pd.roll_pd == 1);
}

void SensorsWidget::_createLabels()
{
    QPoint iconPos[3] = {{18, 176}, {148, 176}, {278, 176}};
    QPoint textPos[3] = {{23, 136}, {156, 132}, {284, 129}};
    QString names[3] = {"yaw", "pitch", "roll"};
    for (int i = 0; i < 3; i++){
        _labels[i] = new QLabel(this);
        _labels[i]->setFixedSize(103, 103);
        _labels[i]->setAlignment(Qt::AlignCenter);
        _labels[i]->move(iconPos[i]);

        _texts[i] = new QLabel(this);
        _texts[i]->setFixedSize(85, 42);
        _texts[i]->move(textPos[i]);
        _texts[i]->setStyleSheet(QString("background-image: url(%1Text.png);").arg(names[i]));
        _texts[i]->setVisible(false);
    }
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
