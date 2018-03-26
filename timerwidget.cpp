#include "timerwidget.hpp"
#include <QMouseEvent>

#include <QPainter>

#define SEC_MS	1000
#define MIN_MS	(SEC_MS * 60)
#define HOUR_MS	(MIN_MS * 60)

TimerWidget::TimerWidget(QWidget *parent):
    QLabel(parent),
    _timer(new QTimer(this))
{
    _initConnections();
    QPixmap picture("C:\\MATE\\Rov_front\\image\\timer.jpg");
    setScaledContents(true);
    setPixmap(picture);
}

void TimerWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &TimerWidget::_updateTimer);
}

void TimerWidget::_updateTimer()
{
    int diff = QTime::currentTime().msecsTo(_lastTime);
    _timeLeft = _time.addMSecs(diff);
    repaint();
}

void TimerWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    if (_timer->isActive()){
        _timer->stop();
        _time = _timeLeft;
        return;
    }
    _timeLeft = _time;
    _lastTime = QTime::currentTime();
    _timer->start(100);
}

void TimerWidget::paintEvent(QPaintEvent *event)
{
    QTime time = _timeLeft;
    QString znak = "";
    if (time.hour() == 23){
        time = QTime(0, 0).addMSecs(_timeLeft.msecsTo(QTime(0, 0).addMSecs(-1)));
        znak = "-";
    }
    QLabel::paintEvent(event);
    QPainter* painter = new QPainter(this);

    QPen pen(Qt::black);
    QFont font = painter->font();
    font.setPixelSize(20);
    if (_timeLeft <= CRITICALTIME || znak == "-"){
        pen = QPen(Qt::red);
        font.setPointSize(26);
    }
    painter->setPen(pen);
    painter->setFont(font);
    painter->drawText(this->rect(), Qt::AlignCenter, znak + time.toString("mm:ss.zzz"));
    painter->end();
}
