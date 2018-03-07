#ifndef ETHERNETCAMERAWIDGET_HPP
#define ETHERNETCAMERAWIDGET_HPP

#include "videowidget.hpp"

#include <QObject>
#include <QWidget>

class EthernetCameraWidget : public VideoWidget
{
public:
    EthernetCameraWidget(int index, QWidget *parent = nullptr);

private:
    QPixmap getPixmap() override;
};

#endif // ITHERNETCAMERAWIDGET_HPP
