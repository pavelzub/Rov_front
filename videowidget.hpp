#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include "imagedetector.hpp"

#include <QObject>
#include <QWidget>
#include <QVideoWidget>
#include <QCamera>
#include <QCameraInfo>
#include <QPainter>
#include <QTimer>
#include <QAction>

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
    void mouseReleaseEvent(QMouseEvent *event);
    virtual QPixmap getPixmap() = 0;

    bool _isEnabled = false;
    QSize _resolution = {1920, 1080};

private:
    const int MAINWIDTH= 962;
    const int SUBWIDTH = 308;
    const QString STARTTIMETTEXT = "Начать распознавание";
    const QString STOPTIMETTEXT = "Остановить распознавание";

    void _initConnections();
    void _initHotKeys();
    void _swap();

    QAction* _swapAct;
    ImageDetector* _detector;
    QAction* _findAction;
    CameraPriority _priority = Sub;
    QTimer* _timer;
};

#endif // VIDEOWIDGET_HPP
