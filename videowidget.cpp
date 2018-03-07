#include "videowidget.hpp"
#include "mainwidget.hpp"
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent):
    QVideoWidget(parent),
    _detector(new ImageDetector(this)),
    _timer(new QTimer(this))
{
    _createMenu();
    _initConnections();
    this->index = index;
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
    if (_timer->isActive() && _detector->figureIsFound())
    {
        painter->drawRect(_detector->getRect());
        font.setPointSize(10);
        painter->setFont(font);
        painter->drawText(_detector->getRect(), Qt::AlignTop, FIGURENAMES[_detector->getType() - 1]);
    }

    painter->end();
}

QPixmap VideoWidget::getPixmap(){}

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
    if (!_isEnabled && _timer->isActive())
    {
        _menuBtnPress();
    }
    _isEnabled = flag;
}

bool VideoWidget::isEnabled()
{
    return _isEnabled;
}

void VideoWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    ((MainWidget*)(this->parent()))->swapCameras(index);
}

void VideoWidget::_createMenu()
{
    _findAction = new QAction(STARTTIMETTEXT, this);
    this->addAction(_findAction);
    this->setContextMenuPolicy(Qt::ActionsContextMenu);
}

void VideoWidget::_menuBtnPress()
{
    if (!_isEnabled) return;
    if (_timer->isActive())
    {
        _findAction->setText(STARTTIMETTEXT);
        _timer->stop();
    }
    else
    {
        _findAction->setText(STOPTIMETTEXT);
        _timer->start(20);
    }
}

void VideoWidget::_initConnections()
{
     connect(_findAction, &QAction::triggered, this, &_menuBtnPress);
     connect(_timer, &QTimer::timeout, this, &_findImage);
}

void VideoWidget::_findImage()
{
    _detector->detectImage(getPixmap());
//    if (_detector->figureIsFound())
//        std::cout << FIGURENAMES[_detector->getType()- 1].toStdString() << std::endl;
//    else
//        std::cout << "NONE" << std::endl;
}
