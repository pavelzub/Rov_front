#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QVideoWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QPainter>

enum CameraType {USB, Ethernet};
enum CameraPriority {Main, Sub};

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(int index, QWidget *parent = nullptr, CameraType type = Ethernet);
    VideoWidget(int index, QCameraInfo camInfo, QWidget *parent = nullptr, CameraType type = Ethernet);
    void setPriority(CameraPriority priority);
    void setIndex(int index);
    void setCamera(QCameraInfo camInfo);
    int index;

private:
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
    void _initConnections();
    void _cameraStateChanged(bool available);
    QPainter* _painter;
    const int MAINWIDTH= 600;
    const int SUBWIDTH = 200;
    QSize _resolution;
    CameraPriority _priority = Sub;
    CameraType _type;
    QCamera* _camera = nullptr;
    void _addCamera(QCamera camera);
};

#endif // VIDEOWIDGET_HPP
