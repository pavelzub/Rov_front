#ifndef TCPCONNETOR_HPP
#define TCPCONNETOR_HPP

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>

#include "settings.hpp"

class TcpConnector : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnector(Settings* settings, QObject *parent = nullptr);
    bool Send(const std::vector<std::uint8_t> data);

signals:
    void dataUpdate(const std::vector<std::uint8_t> data);
    void Connect();
    void Disconnect();

private:
    const quint16 HOST_PORT = 2090;

    void _initConnections();
    void _connect();
    void _onReadyRead();
    void _onConnected();
    void _onDisconnected();
    void _onError(QAbstractSocket::SocketError error);
    void _updateIp();

    QTcpSocket* _socket;
    Settings* _settings;
    QString HOST = "192.168.88.251";
};

#endif // TCPCONNETOR_HPP
