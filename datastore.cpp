#include "datastore.hpp"

DataStore::DataStore(QObject *parent) : QObject(parent)
{
    _initTimer();
    _initConnections();
}

void DataStore::SetAxisX(int axis)
{
    _control.axis_x = static_cast<std::int8_t>(axis * 100 / SHRT_MAX);
}

void DataStore::SetAxisY(int axis)
{
    _control.axis_y = static_cast<std::int8_t>(axis * 100 / SHRT_MAX);
}

void DataStore::SetAxisZ(int axis)
{
    _control.axis_z = static_cast<std::int8_t>(axis * 100 / SHRT_MAX);
}

void DataStore::SetAxisW(int axis)
{
    _control.axis_w = static_cast<std::int8_t>(axis * 100 / SHRT_MAX);
}

void DataStore::SetManRotateRigth(int axis)
{
    _control.manipulator_rotate = static_cast<char>(axis);
}

void DataStore::SetManRotateLLeft(int axis)
{
    _control.manipulator_rotate = static_cast<char>(-axis);
}

void DataStore::SetManOpen(int axis)
{
    _control.manipulator_open_close = static_cast<char>(axis);
}

void DataStore::SetManClose(int axis)
{
    _control.manipulator_open_close = static_cast<char>(-axis);
}

void DataStore::_initTimer()
{
    _timer = new QTimer(this);
    _timer->start(20);
}

void DataStore::_initConnections()
{
    connect(_timer, &QTimer::timeout, this, &DataStore::_onTick);
    connect(&_connector, &TcpConnector::dataUpdate, this, &DataStore::_getPackage);
}

void DataStore::_onTick()
{
    std::cout << "controll:" << (int)_control.axis_x << " " << (int)_control.axis_y << " " << (int)_control.axis_z << " " << (int)_control.axis_w << " " << (int)_control.manipulator_rotate << " " << (int)_control.manipulator_open_close;
    std::cout << "\t\t\t telemetry:"  << _telimetry.pitch << " " << _telimetry.roll << " " << _telimetry.yaw << " " << _telimetry.depth;
    _connector.Send(_control.serialize());
    std::cout << std::endl;
}

void DataStore::_getPackage(const std::vector<uint8_t> &package)
{
    switch (package[0]) {
        case rov_types::rov_telimetry::meta().packet_id:
            _telimetry.deserialize(package);
            emit(telimetryUpdate(_telimetry.yaw, _telimetry.pitch, _telimetry.roll));
            break;
    }
}
