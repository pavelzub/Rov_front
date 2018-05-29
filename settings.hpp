#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <QSettings>

class Settings : public QSettings
{
    Q_OBJECT
public:
    Settings(QString fileName, QSettings::Format format);
    void joystickNeedUpdate();
    void cameraNeedsUpdate();
    void serverIpNeedUpdate();

signals:
    void joystickUpdate();
    void camerasUpdate();
    void serverIpUpdate();

};

#endif // SETTINGS_HPP
