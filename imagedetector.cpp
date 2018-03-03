#include "imagedetector.hpp"
#include "vector"
#include "iostream"
#include <QPainter>
#include <algorithm>
#include <iostream>

#define sqr(x) ((x)*(x))

ImageDetector::ImageDetector(QObject *parent) : QObject(parent)
{

}

FoundFigure ImageDetector::detectImage(QPixmap pixmap)
{
    FoundFigure figure = _detectFigure(pixmap);
    FoundFigure text = _detectText(pixmap);
    return figure.type == Type::NONE ? text : figure;
}

FoundFigure ImageDetector::_detectFigure(QPixmap pixmap)
{
        FoundFigure result;
        cv::Mat image = _getGrauScaleMat(pixmap.toImage());
        std::vector<std::vector<cv::Point> > contours;

        double cannyParams = cv::threshold(image, image, 0, 255, CV_THRESH_BINARY_INV + CV_THRESH_OTSU);
        cv::Canny(image, image, cannyParams, cannyParams / 2.0F);
        cv::findContours(image, contours, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
        cv::drawContours(image, contours, -1, cv::Scalar(100,200,255));
//        cv::imshow("ASD", image);
//        cv::waitKey(1);

        for (std::size_t i = 0; i < contours.size(); i++)
        {
            if (contours.at(i).size() < 5) continue;
            if (std::fabs(cv::contourArea(contours.at(i))) < 300.0) continue;

            static std::vector<cv::Point> hull;
            cv::convexHull(contours.at(i), hull, true);
            cv::approxPolyDP(hull, hull, 15, true);
            if (!cv::isContourConvex(hull)) continue;

            cv::RotatedRect bEllipse = cv::fitEllipse(contours.at(i));
            FigureColor color = _getFigureColor(pixmap.toImage().pixel((int)bEllipse.center.x, (int)bEllipse.center.y));
            if (color == FigureColor::OTHER || hull.size() > 4) continue;

            QPoint min = {INT_MAX, INT_MAX};
            QPoint max = {0, 0};
            for (auto i : hull){
                min.setX(qMin(min.x(), i.x));
                min.setY(qMin(min.y(), i.y));
                max.setX(qMax(max.x(), i.x));
                max.setY(qMax(max.y(), i.y));
            }

            result.rect = QRect(min, max);
            result.type = (Type)((hull.size() - 3) * 3 + color);
            return result;
        }

    return result;
}

FoundFigure ImageDetector::_detectText(QPixmap pixmap)
{
    FoundFigure result;
    try {
        cv::Mat img_scene = _getGrauScaleMat(pixmap.toImage());
        std::vector<cv::KeyPoint> keypoints_scene;

        int minHessian = 400;
        cv::SurfFeatureDetector detector(minHessian);
        detector.detect(img_scene, keypoints_scene);

        cv::SurfDescriptorExtractor extractor;
        cv::Mat descriptors_scene;
        extractor.compute(img_scene, keypoints_scene, descriptors_scene);

        for (int i = 0; i < 6; i++){
//            cv::Mat img_object = cv::imread("C://MATE//Rov_front//" + TEMPLATESPATH[i].toStdString(), CV_LOAD_IMAGE_GRAYSCALE);
            cv::Mat img_object = cv::imread("templates//1.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//            cv::imshow( "Good", img_object );
//            cv::waitKey(1);


            std::vector<cv::KeyPoint> keypoints_object;
            detector.detect(img_object, keypoints_object);

            cv::Mat descriptors_object;
            extractor.compute(img_object, keypoints_object, descriptors_object);

            cv::FlannBasedMatcher matcher;
            cv::vector< cv::DMatch > matches;
            matcher.match( descriptors_object, descriptors_scene, matches );

            double max_dist = 0; double min_dist = 100;

            for( int i = 0; i < descriptors_object.rows; i++ )
            {
                double dist = matches[i].distance;
                if( dist < min_dist ) min_dist = dist;
                if( dist > max_dist ) max_dist = dist;
            }

            std::vector< cv::DMatch > good_matches;

            for( int i = 0; i < descriptors_object.rows; i++ )
            {
                if( matches[i].distance < 3 * min_dist )
                {
                    good_matches.push_back( matches[i]);
                }
            }

//            cv::Mat img_matches;

//            cv::drawMatches( img_object, keypoints_object, img_scene, keypoints_scene,
//            good_matches, img_matches, cv::Scalar::all(-1), cv::Scalar::all(-1),
//            std::vector<char>(), cv::DrawMatchesFlags::NOT_DRAW_SINGLE_POINTS );

            std::vector<cv::Point2f> obj;
            std::vector<cv::Point2f> scene;

            for( int i = 0; i < good_matches.size(); i++ )
            {
                obj.push_back( keypoints_object[ good_matches[i].queryIdx].pt );
                scene.push_back( keypoints_scene[ good_matches[i].trainIdx].pt );
            }

            cv::Mat H = cv::findHomography(obj, scene, CV_RANSAC);
            std::vector<cv::Point2f> obj_corners(4);
            obj_corners[0] = cvPoint(0,0); obj_corners[1] = cvPoint( img_object.cols, 0 );
            obj_corners[2] = cvPoint( img_object.cols, img_object.rows ); obj_corners[3] = cvPoint( 0, img_object.rows );
            std::vector<cv::Point2f> scene_corners(4);

            cv::perspectiveTransform(obj_corners, scene_corners, H);

//            cv::line( img_matches, scene_corners[0] + cv::Point2f( img_object.cols, 0), scene_corners[1] + cv::Point2f( img_object.cols, 0), cv::Scalar(0, 255, 0), 4 );
//            cv::line( img_matches, scene_corners[1] + cv::Point2f( img_object.cols, 0), scene_corners[2] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );
//            cv::line( img_matches, scene_corners[2] + cv::Point2f( img_object.cols, 0), scene_corners[3] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );
//            cv::line( img_matches, scene_corners[3] + cv::Point2f( img_object.cols, 0), scene_corners[0] + cv::Point2f( img_object.cols, 0), cv::Scalar( 0, 255, 0), 4 );

//            std::cout << scene_corners[0].x + cv::Point2f( img_object.cols, 0).x << " " << scene_corners[0].y + cv::Point2f( img_object.cols, 0).y << std::endl;
//            std::cout << scene_corners[1].x + cv::Point2f( img_object.cols, 0).x << " " << scene_corners[1].y + cv::Point2f( img_object.cols, 0).y << std::endl;
//            std::cout << scene_corners[2].x + cv::Point2f( img_object.cols, 0).x << " " << scene_corners[2].y + cv::Point2f( img_object.cols, 0).y << std::endl;
//            std::cout << scene_corners[3].x + cv::Point2f( img_object.cols, 0).x << " " << scene_corners[3].y + cv::Point2f( img_object.cols, 0).y << std::endl << std::endl;
//            cv::imshow( "image_" + QString::number(i).toStdString(), img_matches );
//            cv::waitKey(1);
            double square = _getSquare(scene_corners);
            if (cv::isContourConvex(scene_corners) && square > 10000 && square < 1000000){
                result.rect = _getRect(scene_corners);
                result.type = (Type)(i + 1);
            }
        }
    } catch (...) {
    }
    return result;
}

FigureColor ImageDetector::_getFigureColor(QColor color)
{
    QColor colors[3] = { QColor(Qt::red), QColor(Qt::yellow), QColor(Qt::blue)};

    for (int i = 0; i < 3; i++){
        double distance = std::sqrt(sqr(colors[i].green() - color.green()) +
                                    sqr(colors[i].red() - color.red()) +
                                    sqr(colors[i].blue() - color.blue()));
        if (distance < COLORTOLERANCE)
            return (FigureColor)(i + 1);
    }
    return FigureColor::OTHER;
}

double ImageDetector::_getSquare(std::vector<cv::Point2f> poitns)
{
    double result;
    for (int i = 0; i < poitns.size(); i++){
        result += poitns[i].x * poitns[(i + 1) % poitns.size()].y;
        result -= poitns[i].y * poitns[(i + 1) % poitns.size()].x;
    }
    return qAbs(result);
}

QRect ImageDetector::_getRect(std::vector<cv::Point2f> poitns)
{
    QPoint min = {INT_MAX, INT_MAX};
    QPoint max = {0, 0};
    for (auto i : poitns){
        min.setX(qMin(min.x(), (int)i.x));
        min.setY(qMin(min.y(), (int)i.y));
        max.setX(qMax(max.x(), (int)i.x));
        max.setY(qMax(max.y(), (int)i.y));
    }
    return QRect(min, max);
}

cv::Mat ImageDetector::_getGrauScaleMat(QImage image)
{
    cv::Mat mat(image.height(),image.width(),CV_8UC4,(void *)image.constBits(),image.bytesPerLine());
    cv::cvtColor(mat, mat, CV_BGR2GRAY);
    cv::GaussianBlur(mat, mat, cv::Size(5, 5), cv::BORDER_REFLECT);
    return mat;
}
