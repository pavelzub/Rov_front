#include "videowidget.hpp"
#include "camerascontrolwidget.hpp"
#include <QString>
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent):
    QVideoWidget(parent),
    _swapAct(new QAction(this)),
    _timer(new QTimer(this))
{
    this->index = index;
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

    if (!_isEnabled) {
        painter->fillRect(QRect(0, 0, this->width(), this->height()), QBrush(Qt::black));
        pen = QPen(Qt::white);
    }

    painter->setFont(font);
    painter->setPen(pen);

    painter->drawText(0, 20, "Камера " + QString::number(index + 1));
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

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
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
    _swapAct->setShortcut(QKeySequence(QString::number(index + 1)));
    addAction(_swapAct);
}

void VideoWidget::_swap()
{
    dynamic_cast<CamerasControlWidget*>(this->parent())->swapCameras(index);
}
