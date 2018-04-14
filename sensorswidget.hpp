#ifndef SENSORSWIDGET_HPP
#define SENSORSWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QList>
#include <QLabel>
#include <QPixmap>

class SensorsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsWidget(QWidget *parent = nullptr);
    void TelimetryChange(float yaw, float pitch, float roll);
    void RollCange(int val);
    void YawCange(int val);

private:
    void _createLabels();
    void _initPixmaps();
    void _createVals();
    QPixmap _createPixmap(float angle, int index);

    QPixmap _pixmaps[3];
    QLabel* _labels[3];
    QLabel* _vals[3];
};

#endif // SENSORSWIDGET_HPP
