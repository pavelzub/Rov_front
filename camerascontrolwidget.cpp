#include "camerascontrolwidget.hpp"
#include <iostream>
#include <QCameraInfo>
#include <QVideoWidget>
#include <QLabel>

CamerasControlWidget::CamerasControlWidget(Settings *settings, QWidget *parent) :
      QWidget(parent),
      _camerasConfigDialog(new CamerasConfigDialog(settings, this)),
      _timer(new QTimer(this))
{
    setFixedSize(WIDTH, HEIGHT);
    _settings = settings;

    _initCameras();
    _createLayout();
    _initConnections();
    _timer->start(100);
}

void CamerasControlWidget::swapCameras(int index)
{
    _widgets[0]->layout()->removeWidget(_cameras[_mainCameraIndex]);
    _widgets[_cam_wid[index]]->layout()->replaceWidget(_cameras[index], _cameras[_mainCameraIndex]);
    _widgets[0]->layout()->addWidget(_cameras[index]);

    _cameras[_mainCameraIndex]->setPriority(CameraPriority::Sub);
    _cameras[index]->setPriority(CameraPriority::Main);

    _cam_wid[_mainCameraIndex] = _cam_wid[index];
    _cam_wid[index] = 0;
    _mainCameraIndex = index;

    emit changeMainCameraIndex(_mainCameraIndex == 1 ? 1 : 0);
}

void CamerasControlWidget::showConfigDialog()
{
    _camerasConfigDialog->show();
}

void CamerasControlWidget::refreshCamerasInfo()
{
    QList<QCameraInfo> camerasInfo = QCameraInfo::availableCameras();

    for (int i = 0; i < 2; i++)
    {
       if (_cameras[i]->isEnabled())
       {
           auto camera = dynamic_cast<USBCameraWidget*>(_cameras[i]);
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
            dynamic_cast<USBCameraWidget*>(_cameras[i])->setCamera(camerasInfo.front());
            camerasInfo.pop_front();
        }
    }
}

void CamerasControlWidget::_initCameras()
{
    _cameras[0] = new USBCameraWidget(0, this);
    _cameras[1] = new USBCameraWidget(1, this);
    _cameras[2] = new EthernetCameraWidget(2, _settings, this);
    _cameras[3] = new EthernetCameraWidget(3, _settings, this);

    _cameras[0]->setPriority(CameraPriority::Main);
}

void CamerasControlWidget::_createLayout()
{
    for (int i = 0; i < 4; i++){
        _widgets[i] = new QWidget(this);
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->setMargin(0);
        layout->addWidget(_cameras[i]);

        _widgets[i]->setLayout(layout);
        _widgets[i]->move(_camerasCoord[i]);
    }
}

void CamerasControlWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &CamerasControlWidget::refreshCamerasInfo);

    for (int i = 0; i < 4; i++)
        connect(_cameras[i], &VideoWidget::needSwap, this, &CamerasControlWidget::swapCameras);
}
