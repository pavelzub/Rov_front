#ifndef PDDIALOG_HPP
#define PDDIALOG_HPP

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QLineEdit>
#include <QList>
#include <QPushButton>

#include "rov_data_types/rov_data_types.hpp"

class PdDialog : public QDialog
{
    Q_OBJECT
public:
    PdDialog(rov_types::rov_enable_pd* rovEnablePd, rov_types::rov_pd* rovPd, QWidget* parent = nullptr);
    void UpdatePd();

signals:
    void PdChange(rov_types::rov_pd);

protected:
    void showEvent(QShowEvent * event);

private:
    void _createLayout();
    void _initConnections();
    void _sendData();
    void _updateData();
    const QList<QString> NAMES = {"Yaw_P", "Yaw_D", "Depth_P", "Depth_D", "Roll_P", "Roll_D", "Roll_Default", "Pitch_P", "Pitch_D", "Pitch_Default"};

    rov_types::rov_enable_pd* _rovEnablePd;
    rov_types::rov_pd* _rovPd;
    QList<QLabel*> _names;
    QList<QLineEdit*> _vals;
    QList<QCheckBox*> _needUpdate;
    QPushButton* _sendBtn;
    QPushButton* _updateBtn;
};

#endif // PDDIALOG_HPP
