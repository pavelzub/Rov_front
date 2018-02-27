#ifndef IMAGEDETECTOR_HPP
#define IMAGEDETECTOR_HPP

#include <QObject>
#include <QBitmap>
#include "opencv2/core/version.hpp"
#include "opencv2/opencv.hpp"

enum Type {NONE, REDTRIANGLE, YELLOWTRIANGLE, BLUETRIANGLE, REDRECT, YELLOWRECT, BLUERECT};
enum FigureColor {OTHER, RED, YELLOW, BLUE};

struct FoundFigure
{
    Type type = NONE;
    QRect rect;
    float angle;
};

class ImageDetector : public QObject
{
    Q_OBJECT
public:
    explicit ImageDetector(QObject *parent = nullptr);
    FoundFigure detectImage(QPixmap &pixmap);

private:
    FoundFigure _detectFigure(QPixmap &pixmap);
    FoundFigure _detectText(QPixmap &pixmap);
    FigureColor _getFigureColor(QColor color);

signals:

public slots:
};

#endif // IMAGEDETECTOR_HPP
