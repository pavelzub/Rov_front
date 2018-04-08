#ifndef MYMAINWIDGET_HPP
#define MYMAINWIDGET_HPP

#include "timerwidget.hpp"
#include "camerascontrolwidget.hpp"
#include "joystick/joystickmediator.hpp"
#include "ethernet/datastore.hpp"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QTimer>
#include <QSettings>

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

private:
    void _createLayout();
    void _initConnections();

    QSettings* _settings;
    JoystickMediator* _joystickMediator;
    DataStore _dataStore;
    TimerWidget* _timerWidget;
    CamerasControlWidget*  _camerasControlWidget;
};

#endif // MYMAINWIDGET_HPP
