#include <QCoreApplication>
#include "udpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    ComClient udp(6667, 6668);

    return a.exec();
}
