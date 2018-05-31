#include "ethernetcamerawidget.hpp"
#include "videostreamparser.hpp"

#include <iostream>

EthernetCameraWidget::EthernetCameraWidget(int index, Settings* settings, QWidget *parent):
    VideoWidget(index, parent)
//    _webSocket(new WebSocket("asda", this))
{
    _settings = settings;
    _updateConfig();
    connect(_settings, &Settings::camerasUpdate, this, &EthernetCameraWidget::_updateConfig);
}

void EthernetCameraWidget::_updateConfig()
{
    QString url = "ws://" + _settings->value("CAMERAS/cam_" + QString::number(_index + 1) + "_url", "192.168.1.255:1234").toString();
    if (_url == url) return;

    _url = url;
    if (thread != nullptr){
        thread->terminate();
//        delete thread;
    }

    thread = new QThread;
//    VideoStreamParser* parser = new VideoStreamParser(url, &_isEnabled);
    _webSocket = new WebSocket("asd");
    _webSocket->moveToThread(thread);
    connect(thread, &QThread::started, _webSocket, &WebSocket::process);
//    connect(_webSocket, &VideoStreamParser::finished, thread, &QThread::quit);
    connect(_webSocket, &WebSocket::newFrame, this, &EthernetCameraWidget::_update);
//    connect(_webSocket, &VideoStreamParser::finished, parser, &VideoStreamParser::deleteLater);
//    connect(_webSocket, &VideoStreamParser::finished, this, &EthernetCameraWidget::_onStopEvent);
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
