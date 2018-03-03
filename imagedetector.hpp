#ifndef IMAGEDETECTOR_HPP
#define IMAGEDETECTOR_HPP

#include <QObject>
#include <QBitmap>
#include "opencv2/core/version.hpp"
#include "opencv2/opencv.hpp"

enum Type {NONE, REDTRIANGLE, YELLOWTRIANGLE, BLUETRIANGLE, REDRECT, YELLOWRECT, BLUERECT};
enum FigureColor {OTHER, RED, YELLOW, BLUE};
static QString FIGURENAMES[6] = {"REDTRIANGLE", "YELLOWTRIANGLE", "BLUETRIANGLE",
                                "REDRECT", "YELLOWRECT", "BLUERECT"};

struct FoundFigure
{
    Type type = NONE;
    QRect rect;
};

class ImageDetector : public QObject
{
    Q_OBJECT
public:
    explicit ImageDetector(QObject *parent = nullptr);
    static FoundFigure detectImage(QPixmap &pixmap);

private:
    static FoundFigure _detectFigure(QPixmap &pixmap);
    static FoundFigure _detectText(QPixmap &pixmap);
    static FigureColor _getFigureColor(QColor color);
};

#endif // IMAGEDETECTOR_HPP
