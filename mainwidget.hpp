#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include "usbcamerawidget.hpp"
#include "ithernetcamerawidget.hpp"
#include "timerwidget.hpp"

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <videowidget.hpp>
#include <QTimer>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void swapCameras(int index);

private:
    void refreshCamerasInfo();
    void _initCameras();
    void _createLayout();
    void _initConnections();

    ImageDetector* _detector;
    TimerWidget* _timerWidget;
    QTimer* _timer;
    VideoWidget* _cameras[4];
    int _mainCameraIndex = 0;
    QVBoxLayout* _mainCameraLayout;
    QHBoxLayout* _subCamerasLayout;
};

#endif // MYMAINWIDGET_HPP
