#ifndef VIDEOWIDGET_HPP
#define VIDEOWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QVideoWidget>

enum CameraType {USB, Ethernet};

class VideoWidget : public QVideoWidget
{
    Q_OBJECT
public:
    VideoWidget(QWidget *parent = nullptr, CameraType type = Ethernet);

private:
    CameraType _type;
};

#endif // VIDEOWIDGET_HPP
