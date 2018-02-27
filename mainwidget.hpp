#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include <QWidget>
#include <QTextEdit>
#include <imagedetector.hpp>
#include <videowidget.hpp>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void swapCameras(int a, int b);
    
private:
    ImageDetector* _detector;
    void _initCameras();
    void _createLayout();
    VideoWidget _cameras[4];
};

#endif // MYMAINWIDGET_HPP
