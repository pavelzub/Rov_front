#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _mainWidget(new MyMainWidget(this)),
      _gamepadManager(new MyGamepadManager(this))
{
    setCentralWidget(_mainWidget);
    initializeConnections();
}

MainWindow::~MainWindow()
{
}

void MainWindow::initializeConnections()
{
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_0, this, &changeAxis_X);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_1, this, &changeAxis_Y);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_2, this, &changeAxis_Z);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_3, this, &changeAxis_A);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_4, this, &changeAxis_B);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_5, this, &changeAxis_C);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_6, this, &changeAxis_D);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_7, this, &changeAxis_E);
    connect(_gamepadManager, &MyGamepadManager::ChangeAxis_8, this, &changeAxis_F);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_0, this, &changeButton_0);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_1, this, &changeButton_1);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_2, this, &changeButton_2);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_3, this, &changeButton_3);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_4, this, &changeButton_4);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_5, this, &changeButton_5);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_6, this, &changeButton_6);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_7, this, &changeButton_7);
    connect(_gamepadManager, &MyGamepadManager::ChangeButton_8, this, &changeButton_8);
    connect(_gamepadManager, &MyGamepadManager::GamepadConnect, this, &gamepadConnect);
    connect(_gamepadManager, &MyGamepadManager::GamepadDisconnect, this, &gamepadDisconnect);
}

void MainWindow::changeAxis_X(double value)
{
    _mainWidget->setAxisText(0, QString("%1").arg(value));
}

void MainWindow::changeAxis_Y(double value)
{
    _mainWidget->setAxisText(1, QString("%1").arg(value));
}

void MainWindow::changeAxis_Z(double value)
{
    _mainWidget->setAxisText(2, QString("%1").arg(value));
}

void MainWindow::changeAxis_A(double value)
{
    _mainWidget->setAxisText(3, QString("%1").arg(value));
}

void MainWindow::changeAxis_B(double value)
{
    _mainWidget->setAxisText(4, QString("%1").arg(value));
}

void MainWindow::changeAxis_C(double value)
{
    _mainWidget->setAxisText(5, QString("%1").arg(value));
}

void MainWindow::changeAxis_D(double value)
{
    _mainWidget->setAxisText(6, QString("%1").arg(value));
}

void MainWindow::changeAxis_E(double value)
{
    _mainWidget->setAxisText(7, QString("%1").arg(value));
}

void MainWindow::changeAxis_F(double value)
{
    _mainWidget->setAxisText(8, QString("%1").arg(value));
}

void MainWindow::changeButton_0(double value)
{
    _mainWidget->setButtonsText(0, QString("%1").arg(value));
}

void MainWindow::changeButton_1(double value)
{
    _mainWidget->setButtonsText(1, QString("%1").arg(value));
}

void MainWindow::changeButton_2(double value)
{
    _mainWidget->setButtonsText(2, QString("%1").arg(value));
}

void MainWindow::changeButton_3(double value)
{
    _mainWidget->setButtonsText(3, QString("%1").arg(value));
}

void MainWindow::changeButton_4(double value)
{
    _mainWidget->setButtonsText(4, QString("%1").arg(value));
}

void MainWindow::changeButton_5(double value)
{
    _mainWidget->setButtonsText(5, QString("%1").arg(value));
}

void MainWindow::changeButton_6(double value)
{
    _mainWidget->setButtonsText(6, QString("%1").arg(value));
}

void MainWindow::changeButton_7(double value)
{
    _mainWidget->setButtonsText(7, QString("%1").arg(value));
}

void MainWindow::changeButton_8(double value)
{
    _mainWidget->setButtonsText(8, QString("%1").arg(value));
}

void MainWindow::gamepadDisconnect()
{
    _mainWidget->disableAll();
}

void MainWindow::gamepadConnect()
{
    _mainWidget->enableAll();
}
