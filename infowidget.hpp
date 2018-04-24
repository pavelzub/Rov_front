#ifndef INFOWIDGET_HPP
#define INFOWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QTimer>

class InfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoWidget(QWidget *parent = nullptr);

protected:
     void showEvent(QShowEvent * event);

private:
    void _createLayout();
    void _initConnetions();

    QTimer* _timer;
};

#endif // INFOWIDGET_HPP
