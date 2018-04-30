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
    DataDebugDialog(rovTypes::rov_telimetry* telimetry, rovTypes::rov_control* control, QWidget* parent = nullptr);
    void Update();

private:
    void _createLayout();

    QList<QLabel*> _telimetryVals;
    QList<QLabel*> _controlVals;
    rovTypes::rov_telimetry* _telimetry;
    rovTypes::rov_control* _control;
};

#endif // DATADEBUGDIALOG_HPP
