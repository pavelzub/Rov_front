#include "mainwindow.hpp"
#include <QCameraInfo>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _mainWidget(new MainWidget(this)),
      _gamepadManager(new MyGamepadManager(this))
{
    QList<QCameraInfo> camerasInfo = QCameraInfo::availableCameras();
    std::cout << camerasInfo.size() << std::endl;
    setCentralWidget(_mainWidget);
    initializeConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeConnections()
{
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_0, this, &changeAxis_X);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_1, this, &changeAxis_Y);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_2, this, &changeAxis_Z);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_3, this, &changeAxis_A);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_4, this, &changeAxis_B);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_5, this, &changeAxis_C);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_6, this, &changeAxis_D);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_7, this, &changeAxis_E);
//    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_8, this, &changeAxis_F);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_0, this, &changeButton_0);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_1, this, &changeButton_1);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_2, this, &changeButton_2);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_3, this, &changeButton_3);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_4, this, &changeButton_4);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_5, this, &changeButton_5);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_6, this, &changeButton_6);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_7, this, &changeButton_7);
//    connect(_gamepadManager, &MyGamepadManager::ChangeButton_8, this, &changeButton_8);
//    connect(_gamepadManager, &MyGamepadManager::GamepadConnect, this, &gamepadConnect);
//    connect(_gamepadManager, &MyGamepadManager::GamepadDisconnect, this, &gamepadDisconnect);
}
