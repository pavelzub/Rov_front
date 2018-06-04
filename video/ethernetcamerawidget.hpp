#ifndef ETHERNETCAMERAWIDGET_HPP
#define ETHERNETCAMERAWIDGET_HPP

#include "videowidget.hpp"

#include <QObject>
#include <QWidget>
#include <QThread>

#include "settings.hpp"
#include "websocket.hpp"

class EthernetCameraWidget : public VideoWidget
{
public:
    EthernetCameraWidget(int _index, Settings *settings, QWidget *parent = nullptr);

private:
    void _update(QPixmap pixmap);
    void _updateConfig();
    void _onStopEvent();
    void _initSocket();

    QString _url;
    Settings* _settings;
    WebSocket* _webSocket;
};

#endif // ITHERNETCAMERAWIDGET_HPP
