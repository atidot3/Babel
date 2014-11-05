#include "udpsocket.h"
#include <iostream>

UdpSocket::UdpSocket(QObject *parent) :
    QObject(parent)
{
    socket = new QUdpSocket(this);
    getPort = 6667;
    sendPort = 6667;
    sendIp = "127.0.0.1";
    socket->bind(QHostAddress::Any, getPort);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void UdpSocket::readyRead() {
    QHostAddress getIp;

    buffer.clear();
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size(), &getIp, &getPort);
}

void UdpSocket::sendData(const QByteArray data) {
    QHostAddress address;

    address.setAddress(sendIp);
    socket->writeDatagram(data, address, sendPort);
}

void UdpSocket::setSendIp(const QString ip) {
    sendIp = ip;
}

const QString UdpSocket::getSendIp() {
    return (sendIp);
}

const QByteArray UdpSocket::getData() {
    return (buffer);
}
