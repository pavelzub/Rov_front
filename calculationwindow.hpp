#ifndef CALCULATIONWINDOW_HPP
#define CALCULATIONWINDOW_HPP

#include <QMainWindow>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QString>
#include <QLabel>

class CalculationWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit CalculationWindow(QWidget *parent = nullptr);

private:
    void _createLayouts();
    void _initConnections();
    QLayout* _createBlock(QString name, QString firstFieldName, QWidget* firstFieldVal, QString secondFieldName, QWidget* secondFieldVal);
    void _calculate();

    QLineEdit* _startUpSpeed;
    QLineEdit* _startHorSpeed;
    QLineEdit* _fallUpSpeed;
    QLineEdit* _fallHorSpeed;
    QLineEdit* _windSpeed;
    QLineEdit* _windAngle;
    QLineEdit* _startAngle;
    QLineEdit* _time;
    QPushButton* _calculateBtn;
    QLabel* _resultAngle;
    QLabel* _resultLen;

};

#endif // CALCULATIONWINDOW_HPP
