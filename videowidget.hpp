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
    virtual QPixmap getPixmap();

    bool _isEnabled = false;
    QSize _resolution = {1920, 1080};

private:
    const int MAINWIDTH= 650;
    const int SUBWIDTH = 200;
    const QString STARTTIMETTEXT = "Начать распознавание";
    const QString STOPTIMETTEXT = "Остановить распознавание";

    void mouseReleaseEvent(QMouseEvent *event);
    void _createMenu();
    void _menuBtnPress();
    void _initConnections();
    void _findImage();

    ImageDetector* _detector;
    QAction* _findAction;
    CameraPriority _priority = Sub;
    QTimer* _timer;
};

#endif // VIDEOWIDGET_HPP
