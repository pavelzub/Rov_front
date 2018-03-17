#include "mainwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent),
      _detector(new ImageDetector(this)),
      _timerWidget(new TimerWidget(this)),
      _timer(new QTimer(this))
{
    _initFfmpeg();
    _initCameras();
    _createLayout();
    _initConnections();
    _timer->start(100);
}

void MainWidget::swapCameras(int index)
{
    _mainCameraLayout->removeWidget(_cameras[_mainCameraIndex]);
    _subCamerasLayout->replaceWidget(_cameras[index], _cameras[_mainCameraIndex]);
    _mainCameraLayout->addWidget(_cameras[index]);

    _cameras[_mainCameraIndex]->setPriority(CameraPriority::Sub);
    _cameras[index]->setPriority(CameraPriority::Main);

    _mainCameraIndex = index;
}

void MainWidget::refreshCamerasInfo()
{
    QList<QCameraInfo> camerasInfo = QCameraInfo::availableCameras();
//    std::cout << "Available USB cameras count: " << camerasInfo.size() << std::endl;

    for (int i = 0; i < 2; i++)
    {
       if (_cameras[i]->isEnabled())
       {
           auto camera = (USBCameraWidget*)_cameras[i];
           auto it = std::find_if(camerasInfo.begin(), camerasInfo.end(),
                                  [&camera](QCameraInfo info) { return info.deviceName() == (camera)->getDeviceName(); }
                   );
           if (it == camerasInfo.end()){
               _cameras[i]->setEnabled(false);
               _cameras[i]->repaint();
           }
           else
               camerasInfo.erase(it);
       }
    }

    for (int i = 0; i < 2; i++){
        if (camerasInfo.size() == 0) break;
        if (!_cameras[i]->isEnabled())
        {
            ((USBCameraWidget*)_cameras[i])->setCamera(camerasInfo.front());
            camerasInfo.pop_front();
        }
    }
}

void MainWidget::_initCameras()
{
    _cameras[0] = new USBCameraWidget(0, this);
    _cameras[1] = new USBCameraWidget(1, this);
    _cameras[2] = new EthernetCameraWidget(2, "udp://127.0.0.1:1234", this);
    _cameras[3] = new EthernetCameraWidget(3, "udp://127.0.0.2:1234", this);

    _cameras[0]->setPriority(CameraPriority::Main);
}

void MainWidget::_createLayout()
{
    QHBoxLayout* mainLayout = new QHBoxLayout;

    QVBoxLayout* leftLayout = new QVBoxLayout;
    QVBoxLayout* rigthLayout = new QVBoxLayout;
    QVBoxLayout* camerasLayout = new QVBoxLayout;
    _mainCameraLayout = new QVBoxLayout;
    _mainCameraLayout->addWidget(_cameras[0]);
    _subCamerasLayout = new QHBoxLayout;
    _subCamerasLayout->addWidget(_cameras[1]);
    _subCamerasLayout->addWidget(_cameras[2]);
    _subCamerasLayout->addWidget(_cameras[3]);
    camerasLayout->addLayout(_mainCameraLayout);
    camerasLayout->addLayout(_subCamerasLayout);

    rigthLayout->addWidget(_timerWidget);
    _timerWidget->setFixedSize(200, 200);
    QPixmap picture("C:\\MATE\\Rov_front\\image\\1.jpg");
    _timerWidget->setScaledContents(true);
    _timerWidget->setPixmap(picture);

    leftLayout->addLayout(camerasLayout);
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rigthLayout);

    this->setLayout(mainLayout);
}

void MainWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &refreshCamerasInfo);
}

void MainWidget::_initFfmpeg()
{
    av_register_all();
    avformat_network_init();
    avcodec_register_all();
}
