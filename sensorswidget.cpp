#include "sensorswidget.hpp"
#include <QPainter>
#include <QDebug>

SensorsWidget::SensorsWidget(QWidget *parent) : QWidget(parent)
{
   setFixedSize(390, 720);
   _initPixmaps();
   _createVals();
   _createLabels();
   TelimetryChange(0, 0, 0, 0);
}

void SensorsWidget::TelimetryChange(float yaw, float pitch, float roll, float depth)
{
    QPixmap pixmap = _createPixmap(yaw, 0);
    _labels[0]->setPixmap(pixmap);
    pixmap = _createPixmap(pitch - 60, 1);
    _labels[1]->setPixmap(pixmap);
    pixmap = _createPixmap(roll - 91, 2);
    _labels[2]->setPixmap(pixmap);
    QString fonttemplate = tr("<font color='White'>%1</font>");
    _vals[3]->setText(fonttemplate.arg(QString().setNum(depth, 'g', 4)));
}

void SensorsWidget::RegChange(rov_types::rov_enable_pd enable_pd)
{
    _texts[0]->setVisible(enable_pd.yaw_pd == 1);
    _texts[1]->setVisible(enable_pd.pitch_pd == 1);
    _texts[2]->setVisible(enable_pd.roll_pd == 1);
    _texts[3]->setVisible(enable_pd.depth_pd == 1);
}

void SensorsWidget::_createLabels()
{
    QPoint iconPos[3] = {{18, 176}, {148, 176}, {278, 176}};
    QPoint textPos[4] = {{23, 136}, {156, 132}, {284, 129}, {17, 323}};
    QString names[4] = {"yaw", "pitch", "roll", "depth"};
    for (int i = 0; i < 3; i++){
        _labels[i] = new QLabel(this);
        _labels[i]->setFixedSize(103, 103);
        _labels[i]->setAlignment(Qt::AlignCenter);
        _labels[i]->move(iconPos[i]);
    }
    for (int i = 0; i < 4; i++){
        _texts[i] = new QLabel(this);
        _texts[i]->setFixedSize(90, 42);
        _texts[i]->move(textPos[i]);
        _texts[i]->setStyleSheet(QString("background-image: url(images/sensors/%1Text.png);").arg(names[i]));
        _texts[i]->setVisible(false);
    }
}

void SensorsWidget::_initPixmaps()
{
    _pixmaps[0] = QPixmap("images\\sensors\\yaw.png");
    _pixmaps[1] = QPixmap("images\\sensors\\pitch.png");
    _pixmaps[2] = QPixmap("images\\sensors\\roll.png");
}

void SensorsWidget::_createVals()
{
    for(int i = 0; i < 4; i++){
        _vals[i] = new QLabel(this);
        _vals[i]->setFont(QFont("DS-Digital", 20));
        _vals[i]->setAlignment(Qt::AlignCenter);
        _vals[i]->setFixedWidth(103);
    }
    _vals[0]->move(18, 286);
    _vals[1]->move(148, 286);
    _vals[2]->move(278, 286);
    _vals[3]->setFixedWidth(245);
    _vals[3]->move(136, 332);
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
