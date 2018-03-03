#include "videowidget.hpp"
#include "mainwidget.hpp"
#include <QMediaObject>
#include <iostream>

VideoWidget::VideoWidget(int index, QWidget *parent):
    QVideoWidget(parent),
    _painter(new QPainter(this)),
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

    _painter->drawText(0, 20, "Камера " + QString::number(index + 1));
    if (_timer->isActive() && _figure.type != Type::NONE)
    {
        _painter->drawRect(_figure.rect);
        font.setPointSize(10);
        _painter->setFont(font);
        _painter->drawText(_figure.rect.left(), _figure.rect.top() - 10, FIGURENAMES[_figure.type - 1]);
    }

    _painter->end();
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
    _isEnabled = flag;
    if (!_isEnabled && _timer->isActive())
        _timer->stop();
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
    QPixmap pixmap = getPixmap();
    _figure = ImageDetector::detectImage(pixmap);
    if (_figure.type != Type::NONE)
        std::cout << FIGURENAMES[_figure.type - 1].toStdString() << std::endl;
    else
        std::cout << "NONE" << std::endl;
}
