#ifndef DATASTORE_HPP
#define DATASTORE_HPP

#include <QObject>
#include <QTimer>
#include "rov_data_types/rov_data_types.hpp"
#include "tcpconnetor.hpp"

class DataStore : public QObject
{
    Q_OBJECT
public:
    explicit DataStore(QObject *parent = nullptr);
    void SetAxisX(int axis);
    void SetAxisY(int axis);
    void SetAxisZ(int axis);
    void SetAxisW(int axis);
    void SetManRotateRigth(int axis);
    void SetManRotateLLeft(int axis);
    void SetManOpen(int axis);
    void SetManClose(int axis);

signals:
    void telimetryUpdate(float yaw, float pitch, float roll);
    void tcpConnect();
    void tcpDisconnect();

private:
    void _initTimer();
    void _initConnections();
    void _onTick();
    void _getPackage(const std::vector<std::uint8_t> &package);

    TcpConnector _connector;
    QTimer* _timer;
    rov_types::rov_telimetry _telimetry;
    rov_types::rov_control _control;
};

#endif // DATASTORE_HPP
