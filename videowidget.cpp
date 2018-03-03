#include "videowidget.hpp"
#include "mainwidget.hpp"
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent, CameraType type):
     QVideoWidget(parent),
     _painter(new QPainter(this))
{
    _type = type;
    this->index = index;
}

VideoWidget::VideoWidget(int index, QCameraInfo camInfo, QWidget *parent, CameraType type):
    QVideoWidget(parent),
    _painter(new QPainter(this))
{
    _type = type;
    this->index = index;
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

    setPriority(Sub);
    _initConnections();
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
//    QList<QCameraInfo> camerasInfo = QCameraInfo::availableCameras();
//    for (auto i : camerasInfo)
//    {
//        std::cout << "Available USB cameras count: " <<  << std::endl;
//    }
//    std::cout << "Available USB cameras count: " << camerasInfo.d << std::endl;
    QVideoWidget::paintEvent(event);
    _painter->begin(this);

    QPen pen = QPen(Qt::black);
    QFont font = _painter->font();
    font.setPointSize (20);

    _painter->setFont(font);
    _painter->setPen(pen);

    if (_camera == nullptr || !_camera->isAvailable()) {
        _painter->fillRect(QRect(0, 0, this->width(), this->height()), QBrush(Qt::black));
        pen = QPen(Qt::white);
        _painter->setPen(pen);
    }

    _painter->drawText(0, 20, "Cam_" + QString::number(index));

    _painter->end();
}

void VideoWidget::_initConnections()
{
//    connect(_camera, &QMediaObject::availabilityChanged, this, &_cameraStateChanged);
}

void VideoWidget::_cameraStateChanged(bool available)
{
    auto s = sender();
    std::cout << "!" << std::endl;
    return;
}

void VideoWidget::setPriority(CameraPriority priority)
{
//    if (_priority == priority) return;
    _priority = priority;

    if (_priority == Sub)
        this->setFixedSize(SUBWIDTH, (int)((double)SUBWIDTH / (double)_resolution.width() * (double)_resolution.height()));
    else
        this->setFixedSize(MAINWIDTH, (int)((double)MAINWIDTH / (double)_resolution.width() * (double)_resolution.height()));

}

void VideoWidget::setCamera(QCameraInfo camInfo)
{

}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    ((MainWidget*)(this->parent()))->swapCameras(index);
}
