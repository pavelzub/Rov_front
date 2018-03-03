#include "imagedetector.hpp"
#include "vector"
#include "iostream"
#include <QPainter>
#include <iostream>

ImageDetector::ImageDetector(QObject *parent) : QObject(parent)
{

}

FoundFigure ImageDetector::detectImage(QPixmap &pixmap)
{
    FoundFigure figure = _detectFigure(pixmap);
    return figure;
//    QString text = _detectText(bitmap);
//    return figure.size() ? figure : text;
}

FoundFigure ImageDetector::_detectFigure(QPixmap &pixmap)
{
        cv::Mat image;
        std::vector<std::vector<cv::Point> > contours;
        QImage images = pixmap.toImage();
        cv::Mat mat(images.height(),images.width(),CV_8UC4,(void *)images.constBits(),images.bytesPerLine());
        FoundFigure result;

        image = mat.clone();
        cv::cvtColor(image, image, CV_BGR2GRAY);
        cv::GaussianBlur(image, image, cv::Size(5, 5), cv::BORDER_REFLECT);
        double cannyParams = cv::threshold(image, image, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
        cv::Canny(image, image, cannyParams, cannyParams / 2.0F);
        cv::findContours(image, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
        cv::drawContours(image, contours, -1, cv::Scalar(100,200,255));
        cv::imshow("ASD", image);
        cv::waitKey(1);

        for (std::size_t i = 0; i < contours.size(); i++)
        {
            if (contours.at(i).size() < 5) continue;
            if (std::fabs(cv::contourArea(contours.at(i))) < 300.0) continue;

            static std::vector<cv::Point> hull;
            cv::convexHull(contours.at(i), hull, true);
            cv::approxPolyDP(hull, hull, 15, true);
            if (!cv::isContourConvex(hull)) continue;

            cv::RotatedRect bEllipse = cv::fitEllipse(contours.at(i));
            FigureColor color = _getFigureColor(images.pixel((int)bEllipse.center.x, (int)bEllipse.center.y));
            if (color == FigureColor::OTHER || hull.size() > 4) continue;

            QPoint min = {INT_MAX, INT_MAX};
            QPoint max = {0, 0};
            for (auto i : hull){
                min.setX(qMin(min.x(), i.x));
                min.setY(qMin(min.y(), i.y));
                max.setX(qMax(max.x(), i.x));
                max.setY(qMax(max.y(), i.y));
            }
            result.rect.setTopLeft(min);
            result.rect.setBottomRight(max);
            result.type = (Type)((hull.size() - 3) * 3 + color);
            return result;
        }

    return result;
}

FoundFigure ImageDetector::_detectText(QPixmap &pixmap)
{
    FoundFigure result;
    return result;
}

FigureColor ImageDetector::_getFigureColor(QColor color)
{
    if (color.red() > 175 && color.green() < 40 && color.blue() < 40) return FigureColor::RED;
    if (color.red() > 175 && color.green() < 40 && color.blue() < 40) return FigureColor::YELLOW;
    if (color.red() > 175 && color.green() < 40 && color.blue() < 40) return FigureColor::BLUE;
    return FigureColor::OTHER;
}
