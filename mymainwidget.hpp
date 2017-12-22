#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include <QWidget>
#include <QTextEdit>

class MyMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyMainWidget(QWidget *parent = nullptr);
    void setAxisText(int index, QString text);
    void setButtonsText(int index, QString text);
    void disableAll();
    void enableAll();

private:
    QTextEdit* _axis[9];
    QTextEdit* _buttons[9];

    void createLayout();
};

#endif // MYMAINWIDGET_HPP
