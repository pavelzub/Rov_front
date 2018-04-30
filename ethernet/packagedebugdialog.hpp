#ifndef PACKAGEDEBUGDIALOG_HPP
#define PACKAGEDEBUGDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QSlider>
#include "rov_data_types/rov_data_types.hpp"

class PackageDebugDialog : public QDialog
{
    Q_OBJECT
public:
    PackageDebugDialog(rovTypes::rov_debug* rovDebug, QWidget* parent = nullptr);

signals:
    void visibleChange(bool);

protected:
    void closeEvent(QCloseEvent * event);
    void showEvent(QShowEvent * event);
    void _createLayout();

    rovTypes::rov_debug* _rovDebug;
    QSlider* _power[8];
};

#endif // PACKAGEDEBUGDIALOG_HPP
