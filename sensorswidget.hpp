#ifndef SENSORSWIDGET_HPP
#define SENSORSWIDGET_HPP

#include <QObject>
#include <QWidget>
#include <QList>
#include <QLabel>
#include <QPixmap>
#include "rov_data_types/rov_data_types.hpp"

class SensorsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SensorsWidget(QWidget *parent = nullptr);
    void TelimetryChange(float yaw, float pitch, float roll, float depth);
    void RollCange(int val);
    void YawCange(int val);
    void RegChange(rov_types::rov_enable_pd enable_pd);

private:
    void _createLabels();
    void _initPixmaps();
    void _createVals();
    QPixmap _createPixmap(float angle, int index);

    QPixmap _pixmaps[3];
    QLabel* _labels[3];
    QLabel* _vals[4];
    QLabel* _texts[4];
};

#endif // SENSORSWIDGET_HPP
