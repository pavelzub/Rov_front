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

class AnusPes : public QObject
{
    Q_OBJECT
public:
    explicit AnusPes(QPixmap *pixmap, QString url, QObject *parent = nullptr);

signals:
    void repaint();
    void finished();

public slots:
    void process();

private:
    QPixmap* _pixmap;
    QString _url;
};

#endif // ANUSPES_HPP
