#ifndef TIMERWIDGET_HPP
#define TIMERWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QTime>
#include <QAction>

class TimerWidget : public QLabel
{
public:
    TimerWidget(QWidget *parent = nullptr);

private:
    void _initConnections();
    void _updateTimer();
    void _initActions();
    void _startPause();
    void _restart();
    void mousePressEvent(QMouseEvent* event);
    void paintEvent(QPaintEvent *event);

    const int WIDTH = 284;
    const int HEIGHT = 39;
    const QTime CRITICALTIME = QTime(0, 5);
    const QTime INITTIME = QTime(0, 15);
    QTimer* _timer;
    QTime _lastTime = QTime(0, 0);
    QTime _time = INITTIME;
    QTime _timeLeft = INITTIME;
    QAction* _startAct;
    QAction* _restartAct;
};

#endif // TIMERWIDGET_HPP
