#ifndef USBCAMERAWIDGET_HPP
#define USBCAMERAWIDGET_HPP

#include "videowidget.hpp"

#include <QObject>
#include <QWidget>

class USBCameraWidget : public VideoWidget
{
public:
    USBCameraWidget(int index, QCameraInfo camInfo, QWidget *parent = nullptr);
    USBCameraWidget(int index, QWidget *parent = nullptr);
    QString getDeviceName();
    void setCamera(QCameraInfo camInfo);

protected:
    QPixmap getPixmap() override;

private:
    QString _deviceName;
    QCamera* _camera = nullptr;
};

#endif // USBCAMERAWIDGET_HPP
