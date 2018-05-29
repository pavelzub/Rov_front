#ifndef SERVERIPDIALOG_HPP
#define SERVERIPDIALOG_HPP

#include <QObject>
#include <QWidget>
#include <QDialog>
#include <QLineEdit>

#include "settings.hpp"

class ServerIpDialog : public QDialog
{
    Q_OBJECT
public:
    ServerIpDialog(Settings *settings, QWidget* parent = nullptr);

private:
    void _createLayout();
    void _btnPress();
    \
    Settings* _settings;
    QLineEdit* _serverAdress;
};

#endif // SERVERIPDIALOG_HPP
