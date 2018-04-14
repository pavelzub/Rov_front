#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

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
    VideoWidget(int _index, QWidget *parent = nullptr);
    void setPriority(CameraPriority priority);
    void setEnabled(bool flag);
    bool isEnabled();
    void setIndex(int _index);

signals:
    void needSwap(int);

protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

    int _index;
    QPixmap* _pixmap;
    bool _isEnabled = false;
    QSize _resolution = {1920, 1080};

private:
    const int MAINWIDTH= 817;
    const int SUBWIDTH = 244;
    const QString STARTTIMETTEXT = "Начать распознавание";
    const QString STOPTIMETTEXT = "Остановить распознавание";

    void _initConnections();
    void _initHotKeys();
    void _swap();

    QAction* _swapAct;
    QAction* _findAction;
    CameraPriority _priority = Sub;
    QTimer* _timer;
};

#endif // VIDEOWIDGET_HPP
