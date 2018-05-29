#include "ethernetcamerawidget.hpp"
#include "videostreamparser.hpp"

#include <iostream>

EthernetCameraWidget::EthernetCameraWidget(int index, Settings* settings, QWidget *parent):
    VideoWidget(index, parent)
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
    }

    thread = new QThread;
    _webSocket = new WebSocket();
    _webSocket->moveToThread(thread);
    connect(_webSocket, &WebSocket::newFrame, this, &EthernetCameraWidget::_update);
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
