#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>
#include "ISocket.hh"

class UdpSocket : public QObject, public ISocket
{
    Q_OBJECT
public:
    explicit UdpSocket(QObject *parent = 0);
    void sendData(const QByteArray);
    const QString getSendIp();
    void setSendIp(const QString);

signals:

public slots:
    void readyRead();
private:
    QByteArray  buffer;
    QUdpSocket   *socket;
    quint16     getPort;
    quint16     sendPort;
    QString     sendIp;
};

#endif // UDPSOCKET_H
