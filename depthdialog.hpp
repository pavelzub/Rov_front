#ifndef DEPTHDIALOG_HPP
#define DEPTHDIALOG_HPP

#include <QDialog>
#include <QLabel>


class DepthDialog : public QDialog
{
public:
    DepthDialog();
    void setDepth(float yaw, float pitch, float roll, float depth);


private:
    void _createLayout();
    QLabel* _depth;
};

#endif // DEPTHDIALOG_HPP
