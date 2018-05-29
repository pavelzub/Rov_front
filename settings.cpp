#include "settings.hpp"

Settings::Settings(QString fileName, Format format):
    QSettings (fileName, format)
{
}

void Settings::joystickNeedUpdate()
{
    emit joystickUpdate();
}

void Settings::cameraNeedsUpdate()
{
    emit camerasUpdate();
}

void Settings::serverIpNeedUpdate()
{
    emit serverIpUpdate();
}
