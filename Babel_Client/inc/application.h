#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>
#include "comclient.h"
#include "comserver.h"

namespace Ui {
class Application;
}

class Application : public QWidget
{
    Q_OBJECT

public:
    explicit Application(QWidget *parent = 0);
    ~Application();
    bool    isCalling;
    void    setPseudo(QString);
    void    setIpAddress(QString);
    QString    getPseudo();
    QString    getIpAddress();
    void setServer(ComServer *);

private slots:

    void on_btCall_clicked();

    void on_btHang_clicked();

    void call();

    void hangUp();

    void on_contactList_clicked(const QModelIndex &index);


private:
    Ui::Application *ui;
    QString     ipAddress;
    QString     pseudo;
    ComClient   *client;
    ComServer   *server;
};

#endif // APPLICATION_H
