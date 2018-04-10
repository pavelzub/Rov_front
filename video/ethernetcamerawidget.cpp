#include "ethernetcamerawidget.hpp"
#include "videostreamparser.hpp"

#include <iostream>

EthernetCameraWidget::EthernetCameraWidget(int index, QSettings* settings, QWidget *parent):
    VideoWidget(index, parent)
{
    _settings = settings;
    UpdateConfig();
}

void EthernetCameraWidget::UpdateConfig()
{
    QString url = "udp://" + _settings->value("CAMERAS/cam_" + QString::number(_index + 1) + "_url", "192.168.1.255:1234").toString();
    if (_url == url) return;

    _url = url;
    if (thread != nullptr){
        thread->terminate();
    }

    thread = new QThread;
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
    *_pixmap = pixmap;
    repaint();
}

void EthernetCameraWidget::_onStopEvent()
{
    setEnabled(false);
}
