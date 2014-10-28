#ifndef COMSERVER_H
#define COMSERVER_H

#include <QString>
#include <QTcpSocket>


class ComServer
{
private:
    QTcpSocket *socket;
public:
    ComServer(QString);
};

#endif // COMSERVER_H
