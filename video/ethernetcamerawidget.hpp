#ifndef ETHERNETCAMERAWIDGET_HPP
#define ETHERNETCAMERAWIDGET_HPP

#include "videowidget.hpp"

#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QThread>

extern "C" {
    #define __STDC_CONSTANT_MACROS
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
}

class EthernetCameraWidget : public VideoWidget
{
public:
    EthernetCameraWidget(int _index, QSettings *settings, QWidget *parent = nullptr);
    void UpdateConfig();

private:
    void _update(QPixmap pixmap);
    void _onStopEvent();

    QString _url;
    QThread* thread = nullptr;
    QSettings* _settings;
};

#endif // ITHERNETCAMERAWIDGET_HPP
