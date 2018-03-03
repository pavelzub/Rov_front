#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include "imagedetector.hpp"

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <videowidget.hpp>
#include <QTimer>
//#include <imagedetector.hpp>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void swapCameras(int index);

private:
    ImageDetector* _detector;
    QTimer* _timer;
    VideoWidget* _cameras[4];
    int _mainCameraIndex = 0;
    QVBoxLayout* _mainCameraLayout;
    QHBoxLayout* _subCamerasLayout;
    void refreshCamerasInfo();
    void _initCameras();
    void _createLayout();
    void _initConnections();
};

#endif // MYMAINWIDGET_HPP
