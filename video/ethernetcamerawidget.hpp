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
    EthernetCameraWidget(int index, QSettings *settings, QWidget *parent = nullptr);
    void UpdateConfig();

private:
    void _update(QPixmap pixmap);
    void _onStopEvent();
    void paintEvent(QPaintEvent *event) override;
    QPixmap getPixmap() override;

    QString _url;
    QThread* thread = nullptr;
    QSettings* _settings;
    QPixmap _pixmap;
};

#endif // ITHERNETCAMERAWIDGET_HPP
