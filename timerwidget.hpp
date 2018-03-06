#ifndef TIMERWIDGET_HPP
#define TIMERWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>

class TimerWidget : public QLabel
{
public:
    TimerWidget(QWidget *parent = nullptr);

private:
    void _initConnections();
    void _updateTimer();
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);

    const QTime CRITICALTIME = QTime(0, 5);
    QTimer* _timer;
    QTime _lastTime = QTime(0, 0);
    QTime _time = QTime(0, 0, 5);
    QTime _timeLeft = QTime(0, 0, 5);
};

#endif // TIMERWIDGET_HPP
