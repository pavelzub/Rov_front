#ifndef CAMERASCONTROLWIDGET_H
#define CAMERASCONTROLWIDGET_H

#include <QWidget>
#include "video/usbcamerawidget.hpp"
#include "video/ethernetcamerawidget.hpp"
#include "video/videowidget.hpp"
#include "video/videostreamparser.hpp"
#include "video/camerasconfigdialog.hpp"

#include <QWidget>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>
#include <QSettings>

class CamerasControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CamerasControlWidget(QSettings* settings, QWidget *parent = nullptr);
    void swapCameras(int index);
    void updateConfig();
    void showConfigDialog();

signals:
    void changeMainCameraIndex(int);

private:
    const int CAMERA_PORT_1 = 1234;
    const int CAMERA_PORT_2 = 1;
    const int WIDTH  = 1280;
    const int HEIGHT = 720;

    void refreshCamerasInfo();
    void _initCameras();
    void _createLayout();
    void _initConnections();
    void _initFfmpeg();

    QSettings* _settings;
    CamerasConfigDialog* _camerasConfigDialog;
    QTimer* _timer;
    VideoWidget* _cameras[4];
    QWidget* _widgets[4];
    const QPoint _camerasCoord[4] = {{402, 45}, {402, 550}, {688, 550}, {973, 550}};
    int _cam_wid[4] = {0, 1, 2, 3};
    int _mainCameraIndex = 0;
    QVBoxLayout* _mainCameraLayout;
    QVBoxLayout* _subCamerasLayout;

};

#endif // CAMERASCONTROLWIDGET_H
