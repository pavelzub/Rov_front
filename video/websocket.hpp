#ifndef WEBSOCKET_HPP
#define WEBSOCKET_HPP

#include <QPixmap>
#include <QObject>
#include <QWebSocket>

class WebSocket : public QObject
{
    Q_OBJECT
public:
    WebSocket(QString url, QObject* parent = nullptr);
    void process();
    void setUrl(QString url);

signals:
    void newFrame(QPixmap pixmap);

private:
    void _initConnections();
    void _connect();
    void _disconnect();
    void _getData(const QByteArray &message);
    void _error(QAbstractSocket::SocketError error);

    QString _url;
    QWebSocket _socket;
};

#endif // WEBSOCKET_HPP
