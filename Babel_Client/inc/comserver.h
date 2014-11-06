#ifndef COMSERVER_H
#define COMSERVER_H

#include <QString>
#include <QTcpSocket>
#include <QHostAddress>
#include <iostream>

class ComServer : public QObject
{
    Q_OBJECT
private:
    QTcpSocket *socket;
    QByteArray buffer;
    QString     ip;
    quint16     port;
    bool        isConnected;
public slots:
    void readyRead();
public:
    explicit ComServer(QObject *parent = 0);
    void sendData(const QByteArray);
    void setIp(const QString);
    void setPort(quint16);
    const QString getIp();
    quint16 getPort();
    void connectToHost();
    void setConnection(bool);
    bool getConnection();
};

#endif // COMSERVER_H
