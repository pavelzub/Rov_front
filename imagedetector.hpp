#ifndef IMAGEDETECTOR_HPP
#define IMAGEDETECTOR_HPP

#include <QObject>
#include <QBitmap>
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp"

enum Type {NONE, REDTRIANGLE, YELLOWTRIANGLE, BLUETRIANGLE, REDRECT, YELLOWRECT, BLUERECT};
enum FigureColor {OTHER, RED, YELLOW, BLUE};
static QString FIGURENAMES[6] = {"REDTRIANGLE", "YELLOWTRIANGLE", "BLUETRIANGLE",
                                "REDRECT", "YELLOWRECT", "BLUERECT"};
static QString TEMPLATESPATH[6] = {"templates//1.jpg", "templates//2.jpg", "templates//3.jpg",
                                   "templates//4.jpg", "templates//5.jpg", "templates//6.jpg"};

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
    static FoundFigure detectImage(QPixmap pixmap);

private:
    static const int COLORTOLERANCE = 100;
    static FoundFigure _detectFigure(QPixmap pixmap);
    static FoundFigure _detectText(QPixmap pixmap);
    static FigureColor _getFigureColor(QColor color);
    static double _getSquare(std::vector<cv::Point2f> poitns);
    static QRect _getRect(std::vector<cv::Point2f> poitns);
    static cv::Mat _getGrauScaleMat(QImage image);
};

#endif // IMAGEDETECTOR_HPP
