#include "tcpconnetor.hpp"
#include <iostream>

TcpConnector::TcpConnector(QObject *parent) :
    QObject(parent),
    _socket(new QTcpSocket(this))
{
    _connect();
    _initConnections();
}

bool TcpConnector::Send(const std::vector<uint8_t> data)
{
    if (_socket->state() != QTcpSocket::ConnectedState) return false;

    _socket->write((const char*)data.data(), data.size());
    return true;
}

void TcpConnector::_initConnections()
{
    connect(_socket, &QTcpSocket::readyRead, this, &TcpConnector::_onReadyRead);
    connect(_socket, &QTcpSocket::connected, this, &TcpConnector::_onConnected);
    connect(_socket, &QTcpSocket::disconnected, this, &TcpConnector::_onDisconnected);
    connect(_socket, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error), this, &TcpConnector::_onError);
}

void TcpConnector::_connect()
{
    if (_socket->state() == QTcpSocket::ConnectedState) return;
    _socket->connectToHost(HOST, HOST_PORT);
}

void TcpConnector::_onReadyRead()
{
    QByteArray data = _socket->readAll();
    emit(dataUpdate(std::vector<uint8_t>(data.begin(), data.end())));
}

void TcpConnector::_onConnected()
{
    emit Connect();
}

void TcpConnector::_onDisconnected()
{
    emit Disconnect();
    _connect();
}

void TcpConnector::_onError(QAbstractSocket::SocketError error)
{
    _connect();
}
