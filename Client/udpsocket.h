#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

class ComClient : public QObject
{
private:
    QObject     *parent;
    QUdpSocket  *getUdpSocket;
    QUdpSocket  *sendUdpSocket;
    quint16     getPort;
    quint16     sendPort;
    typedef struct {
        int size;
        void *data;
    } Datagram;

public slots :
    void getData();
public:
    ComClient(int, int, QObject *);
    void sendData(int size, char *data);
};

#endif // UDPSOCKET_H
