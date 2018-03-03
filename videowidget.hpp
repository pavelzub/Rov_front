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
    VideoWidget(int index, QWidget *parent = nullptr);
    void setPriority(CameraPriority priority);
    void setEnabled(bool flag);
    bool isEnabled();
    void setIndex(int index);
    int index;

protected:
    void paintEvent(QPaintEvent *event);

    QPainter* _painter;
    bool _isEnabled = false;
    QSize _resolution = {1920, 1080};

private:
    const int MAINWIDTH= 650;
    const int SUBWIDTH = 200;

    void mouseReleaseEvent(QMouseEvent *event);

    CameraPriority _priority = Sub;
};

#endif // VIDEOWIDGET_HPP
