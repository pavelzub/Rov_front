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
    _createShortcuts();
    _initConnections();
    setScaledContents(true);
    setFixedSize(WIDTH, HEIGHT);
    move(48, 77);
}

void TimerWidget::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &TimerWidget::_updateTimer);
    connect(_startAct, &QShortcut::activated, this, &TimerWidget::_startPause);
    connect(_restartAct, &QShortcut::activated, this, &TimerWidget::_restart);
}

void TimerWidget::_updateTimer()
{
    int diff = QTime::currentTime().msecsTo(_lastTime);
    _timeLeft = _time.addMSecs(diff);
    repaint();
}

void TimerWidget::_createShortcuts()
{
    _startAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_S), this);
    _restartAct = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this);
}

void TimerWidget::_startPause()
{
    if (_timer->isActive()){
        _timer->stop();
        _time = _timeLeft;
        return;
    }
    _timeLeft = _time;
    _lastTime = QTime::currentTime();
    _timer->start(100);
}

void TimerWidget::_restart()
{
    _timeLeft = _time = _lastTime = INITTIME;
    repaint();
}

void TimerWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton) return;
    _startPause();
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
    QPainter painter(this);

    QPen pen(Qt::white);
    QFont font = QFont("After Disaster");
    font.setPixelSize(40);
    if (_timeLeft <= CRITICALTIME || znak == "-"){
        pen = QPen(Qt::red);
    }
    painter.setPen(pen);
    painter.setFont(font);
    painter.drawText(this->rect(), Qt::AlignCenter, znak + time.toString("mm:ss:zzz"));
    painter.end();
}
