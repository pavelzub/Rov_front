#include "videowidget.hpp"
#include "mainwidget.hpp"
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent):
    QVideoWidget(parent),
    _painter(new QPainter(this))
{
    this->index = index;
    setPriority(Sub);
}

void VideoWidget::paintEvent(QPaintEvent *event)
{
    QVideoWidget::paintEvent(event);
    _painter->begin(this);

    QPen pen = QPen(Qt::black);
    QFont font = _painter->font();
    font.setPointSize (20);

    if (!_isEnabled) {
        _painter->fillRect(QRect(0, 0, this->width(), this->height()), QBrush(Qt::black));
        pen = QPen(Qt::white);
    }

    _painter->setFont(font);
    _painter->setPen(pen);
    _painter->drawText(0, 20, "Камера_" + QString::number(index + 1));

    _painter->end();
}

void VideoWidget::setPriority(CameraPriority priority)
{
    _priority = priority;

    if (_priority == Sub)
        this->setFixedSize(SUBWIDTH, (int)((double)SUBWIDTH / (double)_resolution.width() * (double)_resolution.height()));
    else
        this->setFixedSize(MAINWIDTH, (int)((double)MAINWIDTH / (double)_resolution.width() * (double)_resolution.height()));

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
    ((MainWidget*)(this->parent()))->swapCameras(index);
}
