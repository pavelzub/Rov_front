#ifndef CAMERASCONFIGDIALOG_HPP
#define CAMERASCONFIGDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QList>

#include "settings.hpp"

class CamerasConfigDialog : public QDialog
{
    Q_OBJECT
public:
    CamerasConfigDialog(Settings* settings, QWidget* parent = nullptr);

private:
    void _createLayout();
    void _btnPress();

    Settings* _settings;
    QList<QLineEdit*> _camerasAdress;
};

#endif // CAMERASCONFIGDIALOG_HPP
