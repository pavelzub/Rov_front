#include "calculationwindow.hpp"
#include <QProcess>
#include <QDir>
#include <QDoubleValidator>
#include <iostream>
#include <QtMath>
#include <QLineF>
#include <QClipboard>
#include <QApplication>

CalculationWindow::CalculationWindow(QWidget *parent) :
    QMainWindow(parent),
    _startUpSpeed(new QLineEdit(this)),
    _startHorSpeed(new QLineEdit(this)),
    _fallUpSpeed(new QLineEdit(this)),
    _fallHorSpeed(new QLineEdit(this)),
    _windSpeed(new QLineEdit(this)),
    _windAngle(new QLineEdit(this)),
    _startAngle(new QLineEdit(this)),
    _time(new QLineEdit(this)),
    _calculateBtn(new QPushButton(this)),
    _resultAngle(new QLabel(this)),
    _resultLen(new QLabel(this))
{
    _createLayouts();
    _initConnections();
}

void CalculationWindow::_createLayouts()
{
    QWidget* mainWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QHBoxLayout* Layout_1 = new QHBoxLayout(this);
    QHBoxLayout* Layout_2 = new QHBoxLayout(this);
    QHBoxLayout* Layout_3 = new QHBoxLayout(this);
    QLayout* startLayout = _createBlock("Взлет", "Вертикальная скорость", _startUpSpeed, "Горизонтальная скорость", _startHorSpeed);
    QLayout* fallLayout = _createBlock("Падение", "Вертикальная скорость", _fallUpSpeed, "Горизонтальная скорость", _fallHorSpeed);
    QLayout* initLayout = _createBlock("Данные старта", "Угол", _startAngle, "Время", _time);
    QLayout* windLayout = _createBlock("Ветер", "Угол", _windAngle, "Уравнение скорости", _windSpeed);
    QVBoxLayout* resultLayout  = new QVBoxLayout(this);

    _startUpSpeed->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _startHorSpeed->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _fallUpSpeed->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _fallHorSpeed->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _windAngle->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _startAngle->setValidator(new QDoubleValidator(0, 100000, 400, this));
    _time->setValidator(new QDoubleValidator(0, 100000, 400, this));

    _resultAngle->setFixedHeight(75);
    _resultLen->setFixedHeight(75);
    _calculateBtn->setText("Расчитать");
    _resultLen->setStyleSheet("font: 18pt;");
    _resultAngle->setStyleSheet("font: 18pt;");
    _calculateBtn->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    _resultAngle->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
    _resultLen->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);

    Layout_1->addLayout(startLayout);
    Layout_1->addLayout(fallLayout);
    Layout_2->addLayout(windLayout);
    Layout_2->addLayout(initLayout);
    resultLayout->addWidget(_resultAngle);
    resultLayout->addWidget(_resultLen);
    Layout_3->addWidget(_calculateBtn);
    Layout_3->addLayout(resultLayout);
    mainLayout->addLayout(Layout_1);
    mainLayout->addLayout(Layout_2);
    mainLayout->addLayout(Layout_3);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);
}

void CalculationWindow::_initConnections()
{
    connect(_calculateBtn, &QPushButton::released, this, &CalculationWindow::_calculate);
}

QLayout *CalculationWindow::_createBlock(QString name, QString firstFieldName, QWidget *firstFieldVal, QString secondFieldName, QWidget *secondFieldVal)
{
    QVBoxLayout* Layout = new QVBoxLayout(this);
    QLabel* Name = new QLabel(this);
    QLabel* Lable_1 = new QLabel(this);
    QLabel* Lable_2 = new QLabel(this);
    Name->setAlignment(Qt::AlignHCenter);
    Name->setStyleSheet("font: 18pt;");
    Name->setText(name);
    Lable_1->setText(firstFieldName);
    Lable_2->setText(secondFieldName);
    QHBoxLayout* Layout_1 = new QHBoxLayout(this);
    QHBoxLayout* Layout_2 = new QHBoxLayout(this);

    Layout->addWidget(Name);
    Layout->addLayout(Layout_1);
    Layout->addLayout(Layout_2);
    Layout_1->addWidget(Lable_1);
    Layout_1->addWidget(firstFieldVal);
    Layout_2->addWidget(Lable_2);
    Layout_2->addWidget(secondFieldVal);

    return Layout;
}

void CalculationWindow::_calculate()
{
    QProcess proc;

    if (!_startHorSpeed->text().size() || !_startUpSpeed->text().size()
            || !_fallHorSpeed->text().size() || !_fallUpSpeed->text().size()
            || !_startAngle->text().size() || !_windAngle->text().size()
            || !_time->text().size() || !_windSpeed->text().size()){
        _resultAngle->setText("Не все поля заполнены");
        _resultLen->clear();
        return;
    }

    double V1 = _startHorSpeed->text().toDouble();
    double v1 = _startUpSpeed->text().toDouble();
    double V2 = _fallHorSpeed->text().toDouble();
    double v2 = _fallUpSpeed->text().toDouble();
    double a = _startAngle->text().toDouble() / 180.0 * M_PI;
    double b = _windAngle->text().toDouble() / 180.0 * M_PI;
    double t = _time->text().toDouble();
    QString speed = _windSpeed->text();

    double fallTime = t * v1 / v2;
    QString request = QString("/python/main.py \"print (integrate(%1, (t, 0, %2)))\"").arg(speed, QString::number(fallTime));
    proc.start("python " + QDir::currentPath() + request);
    proc.waitForFinished(-1);
    QString out = proc.readAllStandardOutput();
    QString err = proc.readAllStandardError();
    if (err.size() || !out.size()){
        _resultAngle->setText(QDir::currentPath() + request);
        _resultLen->clear();
        QApplication::clipboard()->setText(QDir::currentPath() + request);
        return;
    }

    double windx = -out.toDouble() * qSin(b);
    double windy = -out.toDouble() * qCos(b);
    double startx = V1 * t * qSin(a);
    double starty = V1 * t * qCos(a);
    double fallx = V2 * fallTime * qSin(a);
    double fally = V2 * fallTime * qCos(a);

    QLineF res(0, 0, windx + startx + fallx, windy + starty + fally);

    _resultAngle->setText("Angle: " + QString::number(res.angle()));
    _resultLen->setText("Length: " + QString::number(res.length()));
}

