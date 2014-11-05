#include <QCoreApplication>
#include "udpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    UdpSocket udp;

    return a.exec();
}
