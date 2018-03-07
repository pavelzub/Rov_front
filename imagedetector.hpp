#ifndef IMAGEDETECTOR_HPP
#define IMAGEDETECTOR_HPP

#include <QObject>
#include <QBitmap>

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
    bool isWorking();
    QRect getRect();
    Type getType();

private slots:
    void _stopDetection();

private:
    bool _isWorking = false;
    Type _type = NONE;
    Type _newType;
    QRect _rect;
    QRect _newRect;
};

#endif // IMAGEDETECTOR_HPP
