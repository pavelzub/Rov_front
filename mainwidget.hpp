#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include "timerwidget.hpp"
#include "camerascontrolwidget.hpp"
#include "joystick/joystickmediator.hpp"
#include "ethernet/datastore.hpp"
#include "joystick/joystickdebugdialog.hpp"
#include "sensorswidget.hpp"
#include "infowidget.hpp"
#include "settings.hpp"
#include "depthdialog.hpp"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);
    void ShowJoysticConfig();
    void ShowJoysticDebug();
    void ShowCamerasConfig();

signals:
    void EnableReg(int);

protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    void _createLayout();
    void _createIcons();
    void _initConnections();

    Settings* _settings;
    JoystickMediator* _joystickMediator;
    DataStore* _dataStore;
    TimerWidget* _timerWidget;
    CamerasControlWidget*  _camerasControlWidget;
    JoystickDebugDialog* _joystickDebugDialog;
    SensorsWidget* _sensorWidget;
    InfoWidget* _infoWidget;
    QLabel* _joysticIcon;
    QLabel* _ethernetIcon;
    DepthDialog* _depthDialog;
};

#endif // MYMAINWIDGET_HPP
