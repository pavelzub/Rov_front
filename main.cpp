#include "mainwindow.hpp"
#include <QApplication>
#include <QStyleFactory>
#undef main

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    w.show();

    return a.exec();
}
