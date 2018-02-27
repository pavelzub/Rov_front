#include "mainwidget.hpp"
#include <iostream>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QCameraInfo>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      _detector(new ImageDetector(this))
{
    _initCameras();
    _createLayout();
    QPixmap test("C:\\keras\\trash\\1.jpg");
    _detector->detectImage(test);
//    QImage q = test.toImage();
    //    q.save("C:\\keras\\trash\\1.bmp", "BMP");
}

void MainWidget::swapCameras(int a, int b)
{   

}

void MainWidget::_initCameras()
{
//    for (int i = 0; i < 4; i++)
//        _cameras[i] = new VideoWidget(this);

//    std::cout << camerasInfo.size() << std::endl;
    _cameras[0].setFixedSize(200, 200);
}

void MainWidget::_createLayout()
{
    QVBoxLayout* mainLayout = new QVBoxLayout;

    QHBoxLayout* camerasLayout = new QHBoxLayout;
    camerasLayout->addWidget(&_cameras[0]);
    QVBoxLayout* subCamerasLayout = new QVBoxLayout;
    subCamerasLayout->addWidget(&_cameras[1]);
    subCamerasLayout->addWidget(&_cameras[2]);
    subCamerasLayout->addWidget(&_cameras[3]);
    camerasLayout->addLayout(subCamerasLayout);

    mainLayout->addLayout(camerasLayout);

    this->setLayout(mainLayout);
}
