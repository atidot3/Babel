#include "mainwindow.h"
#include "application.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    newApplication = new Application(); // Be sure to destroy you window somewhere
    newApplication->show();
    this->close();
}
