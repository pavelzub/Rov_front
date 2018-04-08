#ifndef CAMERASCONFIGDIALOG_HPP
#define CAMERASCONFIGDIALOG_HPP

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QSettings>
#include <QLineEdit>
#include <QList>

class CamerasConfigDialog : public QDialog
{
    Q_OBJECT
public:
    CamerasConfigDialog(QSettings* settings, QWidget* parent = nullptr);

signals:
    void configUpdate();

private:
    void _createLayout();
    void _btnPress();

    QSettings* _settings;
    QList<QLineEdit*> _camerasAdress;
};

#endif // CAMERASCONFIGDIALOG_HPP
