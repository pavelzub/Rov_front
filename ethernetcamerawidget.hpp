#ifndef ETHERNETCAMERAWIDGET_HPP
#define ETHERNETCAMERAWIDGET_HPP

#include "videowidget.hpp"

#include <QObject>
#include <QWidget>

extern "C" {
    #define __STDC_CONSTANT_MACROS
    #include <libavformat/avformat.h>
    #include <libavutil/dict.h>
}

class EthernetCameraWidget : public VideoWidget
{
public:
    EthernetCameraWidget(int index, QString  url, QWidget *parent = nullptr);

private:
    void _update();
    void _onStopEvent();
    void paintEvent(QPaintEvent *event);
    QPixmap getPixmap() override;
    QPixmap* _pixmap;
};

#endif // ITHERNETCAMERAWIDGET_HPP
