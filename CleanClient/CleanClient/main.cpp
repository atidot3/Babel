#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ui client;
    client.show();

    return a.exec();
}
