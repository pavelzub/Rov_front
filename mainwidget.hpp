#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include "usbcamerawidget.hpp"
#include "ethernetcamerawidget.hpp"
#include "timerwidget.hpp"
#include "videowidget.hpp"
#include "videostreamparser.hpp"

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void swapCameras(int index);

private:
    const int CAMERA_PORT_1 = 1234;
    const int CAMERA_PORT_2 = 2;

    void refreshCamerasInfo();
    void _initCameras();
    void _createLayout();
    void _initConnections();
    void _initFfmpeg();

    ImageDetector* _detector;
    TimerWidget* _timerWidget;
    QTimer* _timer;
    VideoWidget* _cameras[4];
    int _mainCameraIndex = 0;
    QVBoxLayout* _mainCameraLayout;
    QHBoxLayout* _subCamerasLayout;
};

#endif // MYMAINWIDGET_HPP
