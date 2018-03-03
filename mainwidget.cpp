#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      _detector(new ImageDetector(this)),
      _timer(new QTimer(this))
{
    _initCameras();
    _createLayout();
    _initConnections();
    _timer->start(100);
}

void MainWidget::swapCameras(int index)
{
    _mainCameraLayout->removeWidget(_cameras[_mainCameraIndex]);
    _subCamerasLayout->removeWidget(_cameras[index]);

    _subCamerasLayout->addWidget(_cameras[_mainCameraIndex]);
    _mainCameraLayout->addWidget(_cameras[index]);

    _cameras[_mainCameraIndex]->setPriority(CameraPriority::Sub);
    _cameras[index]->setPriority(CameraPriority::Main);

    _mainCameraIndex = index;
//    std::swap(_cameras[index], _cameras[_mainCameraIndex]);
//    _cameras[0]->index = _mainCameraIndex;
    //    _cameras[index]->index = index;
}

void MainWidget::refreshCamerasInfo()
{

}

void MainWidget::_initCameras()
{
    QList<QCameraInfo> camerasInfo = QCameraInfo::availableCameras();
    std::cout << "Available USB cameras count: " << camerasInfo.size() << std::endl;

    //_cameras[2] = new VideoWidget(2, this, CameraType::Ethernet);
    //_cameras[3] = new VideoWidget(3, this, CameraType::Ethernet);

    for (int i = 0; i < 4; i++)
    {
       if (i < camerasInfo.size())
           _cameras[i] = new VideoWidget(i, camerasInfo[i], this, CameraType::USB);
        else
           _cameras[i] = new VideoWidget(i, this, CameraType::USB);
    }
    _cameras[0]->setPriority(CameraPriority::Main);

}

void MainWidget::_createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QVBoxLayout* camerasLayout = new QVBoxLayout;
    _mainCameraLayout = new QVBoxLayout;
    _mainCameraLayout->addWidget(_cameras[0]);
    _subCamerasLayout = new QHBoxLayout;
    _subCamerasLayout->addWidget(_cameras[1]);
    _subCamerasLayout->addWidget(_cameras[2]);
    _subCamerasLayout->addWidget(_cameras[3]);
    camerasLayout->addLayout(_mainCameraLayout);
    camerasLayout->addLayout(_subCamerasLayout);

    mainLayout->addLayout(camerasLayout);

    this->setLayout(mainLayout);
}

void MainWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &refreshCamerasInfo);
//    connect(_cameras[0], &QVideoWidget::mouseReleaseEvent, this, &_cameraPress);
}
