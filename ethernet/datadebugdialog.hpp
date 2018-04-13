#ifndef DATADEBUGDIALOG_HPP
#define DATADEBUGDIALOG_HPP

#include <QDialog>
#include <QWidget>
#include <QString>
#include <QList>
#include <QLabel>
#include "rov_data_types/rov_data_types.hpp"

class DataDebugDialog : public QDialog
{
    Q_OBJECT
public:
    DataDebugDialog(rov_types::rov_telimetry* telimetry, rov_types::rov_control* control, QWidget* parent = nullptr);
    void Update();

private:
    void _createLayout();

    QList<QLabel*> _telimetryVals;
    QList<QLabel*> _controlVals;
    rov_types::rov_telimetry* _telimetry;
    rov_types::rov_control* _control;
};

#endif // DATADEBUGDIALOG_HPP
