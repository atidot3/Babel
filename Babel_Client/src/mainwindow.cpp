#include "mainwindow.h"
#include "application.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new ComServer();
    server->connectToHost();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString ipAddress;
    QString pseudo;

    ipAddress = ui->tvIpServer->text();
    pseudo = ui->tvPseudo->text();
    if (ipAddress != NULL && pseudo != NULL)
    {
        if (pseudo != "")
        {
            if (ipAddress == "")
                newApplication->setIpAddress("127.0.0.1");
            newApplication = new Application();
            newApplication->setServer(server);
            newApplication->setPseudo(pseudo);
            newApplication->show();
            this->close();
        }
    }
}
