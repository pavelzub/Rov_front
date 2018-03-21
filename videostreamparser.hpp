#ifndef ANUSPES_HPP
#define ANUSPES_HPP

#include <QObject>
#include <QPixmap>

extern "C" {
    #define __STDC_CONSTANT_MACROS
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libswscale/swscale.h>
}

typedef void (*repaintFunc)();

class VideoStreamParser : public QObject
{
    Q_OBJECT
public:
    explicit VideoStreamParser(QPixmap *pixmap, QString url, bool* enable, QObject *parent = nullptr);

signals:
    void repaint();
    void finished();

public slots:
    void process();

private:
    QPixmap frameToQPixmap(AVFrame *src_frame, AVCodecContext *dec);
    bool _init();

    QPixmap* _pixmap;
    QString _url;
    AVFormatContext* _mFormatContext = NULL;
    int _mDataStreamIdx;
    AVCodecContext* _mVideoDecodeContext;
    int _mVideoStreamIdx;
    AVCodecContext* _dec_ctx;
    bool * _enable;
};

#endif // ANUSPES_HPP
