#include "usbcamerawidget.hpp"

USBCameraWidget::USBCameraWidget(int index, QWidget *parent):
    VideoWidget(index, parent)
{

}

USBCameraWidget::USBCameraWidget(int index, QCameraInfo camInfo, QWidget *parent):
    VideoWidget(index, parent)
{
    setCamera(camInfo);
}

QString USBCameraWidget::getDeviceName()
{
    return _deviceName;
}

void USBCameraWidget::setCamera(QCameraInfo camInfo)
{
    _deviceName = camInfo.deviceName();
    _camera = new QCamera(camInfo);
    _camera->setViewfinder(this);
    _camera->setCaptureMode(QCamera::CaptureStillImage);
    _camera->load();

    QList<QSize> resolutions = _camera->supportedViewfinderResolutions();
    auto settings = _camera->viewfinderSettings();
    auto frameRates = _camera->supportedViewfinderFrameRateRanges();
    _resolution = resolutions.back();
    settings.setResolution(_resolution);
    settings.setMinimumFrameRate(frameRates.back().maximumFrameRate);
    _camera->setViewfinderSettings(settings);
    _camera->start();
    _isEnabled = true;
}
