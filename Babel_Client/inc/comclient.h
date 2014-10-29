#ifndef COMCLIENT_H
#define COMCLIENT_H

#include <QString>
#include <QUdpSocket>

class ComClient
{
private:
    QUdpSocket  *getUdpSocket;
    QUdpSocket  *sendUdpSocket;
    int                 getPort;
    int                 sendPort;
public:
    ComClient(int, int, QObject *);
    void sendData(char *);
};

#endif // COMCLIENT_H
