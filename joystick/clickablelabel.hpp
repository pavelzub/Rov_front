#ifndef CLICKABLELABEL_HPP
#define CLICKABLELABEL_HPP

#include <QObject>
#include <QWidget>
#include <QLabel>

class ClickableLabel : public QLabel
{
    Q_OBJECT
public:
    ClickableLabel(QWidget *parent = nullptr);

signals:
    void clicked();

protected:
    void mousePressEvent(QMouseEvent *event);
};

#endif // CLICKABLELABEL_HPP
