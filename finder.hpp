#ifndef FINDER_HPP
#define FINDER_HPP

#include <QObject>
#include "imagedetector.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/nonfree/features2d.hpp"
#include "opencv2/opencv.hpp"

class Finder : public QObject
{
    Q_OBJECT
public:
    explicit Finder(Type* type, QRect* rect, QPixmap pixmap, QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void process();

private:
    const int COLORTOLERANCE = 100;
    const int MAXSQUARE = 1000000;
    const int MINSQUARE = 10000;

    QPixmap _pixmap;
    Type* _type;
    QRect* _rect;

    void _detectFigure(QPixmap pixmap);
    void _detectText(QPixmap pixmap);

    FigureColor _getFigureColor(QColor color);
    float _getSquare(std::vector<cv::Point2f> poitns);
    QRect _getRect(std::vector<cv::Point2f> poitns);
    cv::Mat _getGrauScaleMat(QImage image);
};

#endif // FINDER_HPP
