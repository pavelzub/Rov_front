#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include <QWidget>
#include <QTextEdit>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void setAxisText(int index, QString text);
    void setButtonsText(int index, QString text);
    void disableAll();
    void enableAll();

private:
    QTextEdit* m_axis[9];
    QTextEdit* m_buttons[9];

    void createLayout();
};

#endif // MYMAINWIDGET_HPP
