#ifndef TCPCONNETOR_HPP
#define TCPCONNETOR_HPP

#include <QObject>
#include <QAbstractSocket>
#include <QTcpSocket>

class TcpConnector : public QObject
{
    Q_OBJECT
public:
    explicit TcpConnector(QObject *parent = nullptr);
    bool Send(const std::vector<std::uint8_t> data);

signals:
    void dataUpdate(const std::vector<std::uint8_t> data);
    void Connect();
    void Disconnect();

private:
    const quint16 HOST_PORT = 2090;
    const QString HOST = "192.168.1.113";

    void _initConnections();
    void _connect();
    void _onReadyRead();
    void _onConnected();
    void _onDisconnected();
    void _onError(QAbstractSocket::SocketError error);
    QTcpSocket* _socket;

};

#endif // TCPCONNETOR_HPP
