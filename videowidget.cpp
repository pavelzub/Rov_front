#include "videowidget.hpp"

VideoWidget::VideoWidget(QWidget *parent, CameraType type):
     QVideoWidget(parent)
{
    _type = type;
}
