#ifndef IMAGEDETECTOR_HPP
#define IMAGEDETECTOR_HPP

#include <QObject>
#include <QBitmap>
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp"

enum Type {NONE, REDTRIANGLE, YELLOWTRIANGLE, BLUETRIANGLE, REDRECT, YELLOWRECT, BLUERECT};
enum FigureColor {OTHER, RED, YELLOW, BLUE};
const QString FIGURENAMES[6] = {"REDTRIANGLE", "YELLOWTRIANGLE", "BLUETRIANGLE",
                                "REDRECT", "YELLOWRECT", "BLUERECT"};
const QString TEMPLATESPATH[6] = {"templates//1.jpg", "templates//2.jpg", "templates//3.jpg",
                                   "templates//4.jpg", "templates//5.jpg", "templates//6.jpg"};

class ImageDetector : public QObject
{
    Q_OBJECT
public:
    explicit ImageDetector(QObject *parent = nullptr);
    void detectImage(QPixmap pixmap);
    bool figureIsFound();
    QRect getRect();
    Type getType();

private:
    const int COLORTOLERANCE = 100;
    const int MAXSQUARE = 1000000;
    const int MINSQUARE = 10000;
    Type _type = NONE;
    QRect _rect;

    void _detectFigure(QPixmap pixmap);
    void _detectText(QPixmap pixmap);
    FigureColor _getFigureColor(QColor color);
    double _getSquare(std::vector<cv::Point2f> poitns);
    QRect _getRect(std::vector<cv::Point2f> poitns);
    cv::Mat _getGrauScaleMat(QImage image);
};

#endif // IMAGEDETECTOR_HPP
