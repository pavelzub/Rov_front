#ifndef VIDEOSURFACE_HPP
#define VIDEOSURFACE_HPP

#include <QAbstractVideoSurface>
#include <QObject>
#include <QPixmap>

class QAbstractVideoSurface;

class VideoSurface : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    VideoSurface(QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);

signals:
    void newFrame(QPixmap);
};

#endif // VIDEOSURFACE_HPP
