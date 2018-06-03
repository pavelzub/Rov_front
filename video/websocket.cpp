#include "websocket.hpp"

WebSocket::WebSocket(QString url, QObject *parent):
    QObject(parent)
{
    _socket.setParent(this);
    _url = "ws://" + url;
    _initConnections();
}

void WebSocket::process()
{
    _socket.open(QUrl(_url));
}

void WebSocket::setUrl(QString url)
{
    _url = "ws://" + url;
    _socket.disconnect();
    _socket.open(QUrl(_url));
}

void WebSocket::_initConnections()
{
    connect(&_socket, &QWebSocket::connected, this, &WebSocket::_connect);
    connect(&_socket, &QWebSocket::disconnected, this, &WebSocket::_disconnect);
    connect(&_socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocket::_error);
    connect(&_socket, &QWebSocket::binaryMessageReceived, this, &WebSocket::_getData);
}

void WebSocket::_connect()
{
    qDebug() << "connect";
}

void WebSocket::_disconnect()
{
    _socket.open(QUrl(_url));
}

void WebSocket::_getData(const QByteArray &message)
{
    qDebug() << "Get data: " << message.size();
    QPixmap p;
    if (!p.loadFromData(message, "JPEG"))
        return;
    newFrame(p);
}

void WebSocket::_error(QAbstractSocket::SocketError error)
{
    _socket.open(QUrl(_url));
}
