#ifndef COMCLIENT_H
#define COMCLIENT_H

#include <QString>
#include <QUdpSocket>

class ComClient : public QObject
{
private:
    QObject     *parent;
    QUdpSocket  *getUdpSocket;
    QUdpSocket  *sendUdpSocket;
    quint16                 getPort;
    quint16                 sendPort;
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

#endif // COMCLIENT_H
