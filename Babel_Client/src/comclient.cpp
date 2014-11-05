#include "comclient.h"
#include <iostream>

ComClient::ComClient(int get, int send, QObject *parent)
{
    this->getPort = get;
    this->sendPort = send;
    this->parent = parent;
    this->sendUdpSocket = new QUdpSocket(parent);
    this->sendUdpSocket->bind(QHostAddress::LocalHost, this->sendPort);
    this->getUdpSocket = new QUdpSocket(parent);
    this->getUdpSocket->bind(QHostAddress::LocalHost, this->getPort);
    connect(this->getUdpSocket,SIGNAL(readyRead()), this, SLOT(getData()));
}

void ComClient::sendData(int size, char *data)
{
    QByteArray datagram;

    datagram.append(QByteArray::number(size, 10));
    datagram.append(data);
    this->sendUdpSocket->writeDatagram(datagram, QHostAddress::LocalHost, this->sendPort);
}

void ComClient::getData() {
    QByteArray buffer;
    QHostAddress sender;

    buffer.resize(this->getUdpSocket->pendingDatagramSize());
    this->getUdpSocket->readDatagram(buffer.data(),buffer.size(),&sender, &this->sendPort);

    std::cout << sender.toString().toUtf8().constData() << std::endl;
}
