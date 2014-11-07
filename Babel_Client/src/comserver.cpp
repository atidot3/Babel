#include "comserver.h"

ComServer::ComServer(QObject *parent) :
    QObject(parent)
{
    isConnected = false;
    socket = new QTcpSocket(this);
    ip = "127.0.0.1";
    port = 8888;
}

void ComServer::connectToHost() {
    QHostAddress ipAddress;

    ipAddress.setAddress(ip);
    socket->connectToHost(ipAddress, port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    if( socket->waitForConnected() ) {
        setConnection(true);
    }
}

void ComServer::sendData(const QByteArray data) {
    if( socket->waitForConnected() ) {
        socket->write(data, data.size());
    }
}

void ComServer::setIp(const QString ip) {
    this->ip = ip;
}

void ComServer::setPort(quint16 port) {
    this->port = port;
}

void ComServer::readyRead() {
    buffer.clear();
    buffer = socket->readAll();
    if (buffer.size() > 0)
        std::cout << "Message : " << buffer.data() << std::endl;
}

const QString ComServer::getIp() {
    return (ip);
}

quint16 ComServer::getPort() {
    return (port);
}

void ComServer::setConnection(bool state) {
    this->isConnected = state;
}

bool ComServer::getConnection() {
    return isConnected;
}
