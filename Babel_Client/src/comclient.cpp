#include "comclient.h"

ComClient::ComClient(int get, int send, QObject *parent)
{
    this->getPort = get;
    this->sendPort = send;
    this->sendUdpSocket = new QUdpSocket(parent);
    this->sendUdpSocket->bind(QHostAddress::LocalHost, this->sendPort);
    this->getUdpSocket = new QUdpSocket(parent);
    this->getUdpSocket->bind(QHostAddress::LocalHost, this->getPort);

}

void ComClient::sendData(char *datagram)
{
    this->sendUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost, this->sendPort);
}
