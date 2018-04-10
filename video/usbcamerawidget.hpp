#ifndef USBCAMERAWIDGET_HPP
#define USBCAMERAWIDGET_HPP

#include "videowidget.hpp"
#include "videosurface.hpp"

#include <QObject>
#include <QWidget>
#include <QTimer>

class USBCameraWidget : public VideoWidget
{
public:
    USBCameraWidget(int _index, QWidget *parent = nullptr);
    QString getDeviceName();
    void setCamera(QCameraInfo camInfo);

private:
    void _initConnections();

    QString _deviceName;
    QCamera* _camera = nullptr;
    VideoSurface* _videoSurface;
    QTimer* _timer;
};

#endif // USBCAMERAWIDGET_HPP
