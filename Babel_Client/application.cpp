#include "application.h"
#include "ui_application.h"
#include <iostream>
#include <string>

Application::Application(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Application)
{
    ui->setupUi(this);
    isCalling = false;
    //ui->contactList->clear();
}

Application::~Application()
{
    delete ui;
}

void Application::on_btCall_clicked()
{
    this->call();
}

void Application::on_btHang_clicked()
{
    this->hangUp();
}

void Application::call()
{
    QString clickedRow;

    if (ui->contactList->currentRow() == -1)
        return;
    isCalling = true;
    ui->btCall->setEnabled(false);
    ui->btHang->setEnabled(true);
    clickedRow = ui->contactList->item(ui->contactList->currentRow())->text();
    ui->tvStatus->setText("Appel en cours :\n" + clickedRow);
}

void Application::hangUp()
{
    if (ui->contactList->currentRow() == -1)
        return;
    isCalling = false;
    ui->btCall->setEnabled(true);
    ui->btHang->setEnabled(false);
    ui->tvStatus->setText("");
}

void Application::on_contactList_clicked(const QModelIndex &index)
{
    if (isCalling == false)
    {
        ui->btCall->setEnabled(true);
        ui->btHang->setEnabled(false);
    }
}
