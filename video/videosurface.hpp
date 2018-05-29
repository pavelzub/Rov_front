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
    VideoSurface(QPixmap* pixmap, QObject *parent = 0);

    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    bool present(const QVideoFrame &frame);

signals:
    void newFrame(QPixmap);

private:
    QPixmap* _pixmap;
};

#endif // VIDEOSURFACE_HPP
