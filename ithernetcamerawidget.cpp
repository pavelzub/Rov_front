#include "ithernetcamerawidget.hpp"
#include "anuspes.hpp"

#include <QThread>

EthernetCameraWidget::EthernetCameraWidget(int index, QString url, QWidget *parent):
    VideoWidget(index, parent),
    _pixmap(new QPixmap())
{
    QThread* thread = new QThread;
    AnusPes* anuspes = new AnusPes(_pixmap, url);

    anuspes->moveToThread(thread);

    connect(thread, &QThread::started, anuspes, &AnusPes::process);
    connect(anuspes, &AnusPes::finished, thread, &QThread::quit);
    connect(anuspes, &AnusPes::repaint, this, &EthernetCameraWidget::_update);
    connect(anuspes, &AnusPes::finished, anuspes, &AnusPes::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void EthernetCameraWidget::_update()
{
    repaint();
}

void EthernetCameraWidget::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);

    painter->drawPixmap(0, 0, *_pixmap);
    painter->end();

    VideoWidget::paintEvent(event);
}

QPixmap EthernetCameraWidget::getPixmap()
{
    return *_pixmap;
}
