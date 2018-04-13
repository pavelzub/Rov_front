#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "mainwidget.hpp"

#include <QMainWindow>
#include <QPixmap>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void paintEvent(QPaintEvent *event);

private:
    void _createShortcuts();

    const int WINDOWHEIGTH = 720;
    const int WINDOWWIDTH = 1280;

    MainWidget* _mainWidget;
    QPixmap* _background;
};

#endif // MAINWINDOW_HPP
