#include "imagedetector.hpp"
#include "finder.hpp"
#include <vector>
#include <iostream>
#include <QThread>

ImageDetector::ImageDetector(QObject *parent) : QObject(parent)
{

}

void ImageDetector::detectImage(QPixmap pixmap)
{
    if (_isWorking) return;
    _isWorking = true;

    _newType = NONE;
    QThread* thread = new QThread;
    Finder* finder = new Finder(&_newType, &_newRect, pixmap);

    finder->moveToThread(thread);

    connect(thread, &QThread::started, finder, &Finder::process);
    connect(finder, &Finder::finished, thread, &QThread::quit);
    connect(finder, &Finder::finished, this, &ImageDetector::_stopDetection);
    connect(finder, &Finder::finished, finder, &Finder::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

bool ImageDetector::figureIsFound()
{
    return _type != NONE;
}

bool ImageDetector::isWorking()
{
    return _isWorking;
}

QRect ImageDetector::getRect()
{
    return _rect;
}

Type ImageDetector::getType()
{
    return _type;
}

void ImageDetector::_stopDetection()
{
    _isWorking = false;
    _type = _newType;
    _rect = _newRect;
}
