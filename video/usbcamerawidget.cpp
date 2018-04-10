#include "usbcamerawidget.hpp"

USBCameraWidget::USBCameraWidget(int index, QWidget *parent):
    VideoWidget(index, parent),
    _timer(new QTimer(this))
{
    _timer->start(20);
    _initConnections();
}

QString USBCameraWidget::getDeviceName()
{
    return _deviceName;
}

void USBCameraWidget::setCamera(QCameraInfo camInfo)
{
    if (!_videoSurface) free(_videoSurface);
    if (!_camera) free(_camera);
    _camera = new QCamera(camInfo);
    _videoSurface = new VideoSurface(_pixmap, this);
    _deviceName = camInfo.deviceName();
    _camera->setViewfinder(_videoSurface);
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

void USBCameraWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, [this](){
        repaint();
    });
}
