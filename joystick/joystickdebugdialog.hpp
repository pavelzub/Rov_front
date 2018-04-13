#ifndef JOYSTICKDEBUGDIALOG_HPP
#define JOYSTICKDEBUGDIALOG_HPP

#include "joystickmediator.hpp"
#include "joystickconfigdialog.hpp"

#include <QDialog>
#include <QObject>
#include <QLabel>
#include <QList>

class JoystickDebugDialog : public QDialog
{
    Q_OBJECT
public:
    JoystickDebugDialog(JoystickMediator* joysticMediator, QWidget* parent = nullptr);

private:
    void _createLayouts();
    void _initConnection(JoystickMediator *joysticMediator);
    void _updateVal(int index, int val);

    QList<QLabel*> _vals;
};

#endif // JOYSTICKDEBUGDIALOG_HPP
