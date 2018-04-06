#ifndef CAMERASCONTROLWIDGET_H
#define CAMERASCONTROLWIDGET_H

#include <QWidget>
#include "video/usbcamerawidget.hpp"
#include "video/ethernetcamerawidget.hpp"
#include "video/videowidget.hpp"
#include "video/videostreamparser.hpp"

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>

class CamerasControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CamerasControlWidget(QWidget *parent = nullptr);
    void swapCameras(int index);

private:
    const int CAMERA_PORT_1 = 1234;
    const int CAMERA_PORT_2 = 1;
    const int WIDTH  = 1280;
    const int HEIGHT = 542;

    void refreshCamerasInfo();
    void _initCameras();
    void _createLayout();
    void _initConnections();
    void _initFfmpeg();

    QTimer* _timer;
    VideoWidget* _cameras[4];
    int _mainCameraIndex = 0;
    QVBoxLayout* _mainCameraLayout;
    QVBoxLayout* _subCamerasLayout;

};

#endif // CAMERASCONTROLWIDGET_H
