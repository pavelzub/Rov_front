#include "ethernetcamerawidget.hpp"
#include "videostreamparser.hpp"
#include <iostream>

#include <QThread>

EthernetCameraWidget::EthernetCameraWidget(int index, QString url, QWidget *parent):
    VideoWidget(index, parent),
    _pixmap(new QPixmap())
{
    QThread* thread = new QThread;
    VideoStreamParser* parser = new VideoStreamParser(_pixmap, url, &_isEnabled);

    parser->moveToThread(thread);

    connect(thread, &QThread::started, parser, &VideoStreamParser::process);
    connect(parser, &VideoStreamParser::finished, thread, &QThread::quit);
    connect(parser, &VideoStreamParser::repaint, this, &EthernetCameraWidget::_update);
    connect(parser, &VideoStreamParser::finished, parser, &VideoStreamParser::deleteLater);
    connect(parser, &VideoStreamParser::finished, this, &EthernetCameraWidget::_onStopEvent);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void EthernetCameraWidget::_update()
{
    repaint();
}

void EthernetCameraWidget::_onStopEvent()
{
    setEnabled(false);
}

void EthernetCameraWidget::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);

    if (_pixmap) std::cout << _pixmap->width() << " " << _pixmap->height() << std::endl;
    painter->drawPixmap(rect(), *_pixmap);
    painter->end();

    VideoWidget::paintEvent(event);
}

QPixmap EthernetCameraWidget::getPixmap()
{
    return *_pixmap;
}
