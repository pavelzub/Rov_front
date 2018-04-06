#include "ethernetcamerawidget.hpp"
#include "videostreamparser.hpp"
#include <iostream>

#include <QThread>

EthernetCameraWidget::EthernetCameraWidget(int index, QString url, QWidget *parent):
    VideoWidget(index, parent)
{
    QThread* thread = new QThread;
    VideoStreamParser* parser = new VideoStreamParser(url, &_isEnabled);

    parser->moveToThread(thread);

    connect(thread, &QThread::started, parser, &VideoStreamParser::process);
    connect(parser, &VideoStreamParser::finished, thread, &QThread::quit);
    connect(parser, &VideoStreamParser::repaint, this, &EthernetCameraWidget::_update);
    connect(parser, &VideoStreamParser::finished, parser, &VideoStreamParser::deleteLater);
    connect(parser, &VideoStreamParser::finished, this, &EthernetCameraWidget::_onStopEvent);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

void EthernetCameraWidget::_update(QPixmap pixmap)
{
    _pixmap = pixmap;
    repaint();
}

void EthernetCameraWidget::_onStopEvent()
{
    setEnabled(false);
}

void EthernetCameraWidget::paintEvent(QPaintEvent *event)
{
    QPainter* painter = new QPainter(this);

    if (_pixmap.size() != QSize(0, 0)){
        painter->drawPixmap(rect(), _pixmap);
    }
    painter->end();

    VideoWidget::paintEvent(event);
}

QPixmap EthernetCameraWidget::getPixmap()
{
    return _pixmap;
}
