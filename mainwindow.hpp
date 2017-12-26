#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <mainwidget.hpp>
#include <gamepadmanager.hpp>
#undef main

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    MainWidget* _mainWidget;
    MyGamepadManager *_gamepadManager;
    void initializeConnections();
    void changeAxis_X(double value);
    void changeAxis_Y(double value);
    void changeAxis_Z(double value);
    void changeAxis_A(double value);
    void changeAxis_B(double value);
    void changeAxis_C(double value);
    void changeAxis_D(double value);
    void changeAxis_E(double value);
    void changeAxis_F(double value);
    void changeButton_0(double value);
    void changeButton_1(double value);
    void changeButton_2(double value);
    void changeButton_3(double value);
    void changeButton_4(double value);
    void changeButton_5(double value);
    void changeButton_6(double value);
    void changeButton_7(double value);
    void changeButton_8(double value);
    void gamepadDisconnect();
    void gamepadConnect();
};

#endif // MAINWINDOW_HPP
