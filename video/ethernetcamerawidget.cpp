#include "ethernetcamerawidget.hpp"

#include <iostream>

EthernetCameraWidget::EthernetCameraWidget(int index, Settings* settings, QWidget *parent):
    VideoWidget(index, parent)
{
    if (index == 3) return;
    _settings = settings;
    _initSocket();
    connect(_settings, &Settings::camerasUpdate, this, &EthernetCameraWidget::_updateConfig);
}

void EthernetCameraWidget::_updateConfig()
{
    QString url = _settings->value("CAMERAS/cam_" + QString::number(_index + 1) + "_url", "192.168.1.124:3090").toString();

    if (_url == url) return;
    _url = url;

    _webSocket->setUrl(_url);
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

void EthernetCameraWidget::_initSocket()
{
    auto thread = new QThread;

    auto url = _settings->value("CAMERAS/cam_" + QString::number(_index + 1) + "_url", "192.168.1.124:3090").toString();
    _webSocket = new WebSocket(url);
    _webSocket->moveToThread(thread);

    connect(thread, &QThread::started, _webSocket, &WebSocket::process);
    connect(_webSocket, &WebSocket::newFrame, this, &EthernetCameraWidget::_update);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
