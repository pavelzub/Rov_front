#include "videowidget.hpp"
#include "camerascontrolwidget.hpp"
#include <QString>
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent):
    QVideoWidget(parent),
    _pixmap(new QPixmap),
    _swapAct(new QAction(this)),
    _timer(new QTimer(this))
{
    this->_index = index;
    _initConnections();
    _initHotKeys();
    setPriority(Sub);
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QVideoWidget::paintEvent(event);
    QPainter* painter = new QPainter(this);

    QPen pen = QPen(Qt::black);
    QFont font = painter->font();
    font.setPointSize(15);

    if (!_isEnabled)
        pen = QPen(Qt::white);

    if (_pixmap->size() != QSize(0, 0)){
        painter->setRenderHint(QPainter::Antialiasing);
        painter->setRenderHint(QPainter::Antialiasing, true);

        QPainterPath path;
        QPixmap pixmap = *_pixmap;
        pixmap = pixmap.scaled(width(), height(), Qt::IgnoreAspectRatio,Qt::FastTransformation);
        path.addRoundedRect(QRectF(0, 0, width(), height()), 10, 10);

        painter->setClipPath(path);
        painter->drawPixmap(0, 0, pixmap);
    }

    painter->setFont(font);
    painter->setPen(pen);
    painter->drawText(5, 20, "Сam " + QString::number(_index + 1));

    painter->end();
}

void VideoWidget::setPriority(CameraPriority priority)
{
    _priority = priority;

    if (_priority == Sub)
        this->setFixedSize(SUBWIDTH, SUBWIDTH * 9 / 16);
    else
        this->setFixedSize(MAINWIDTH, MAINWIDTH * 9 / 16);

}

void VideoWidget::setEnabled(bool flag)
{
    _isEnabled = flag;
}

bool VideoWidget::isEnabled()
{
    return _isEnabled;
}

void VideoWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    _swap();
}

void VideoWidget::_initConnections()
{
    connect(_swapAct, &QAction::triggered, this, &VideoWidget::_swap);
}

void VideoWidget::_initHotKeys()
{
    _swapAct->setShortcut(QKeySequence(QString::number(_index + 1)));
    addAction(_swapAct);
}

void VideoWidget::_swap()
{
    emit needSwap(_index);
}
