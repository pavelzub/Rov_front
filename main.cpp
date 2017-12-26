#include "mainwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    //test2
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
