#ifndef APPLICATION_H
#define APPLICATION_H

#include <QWidget>

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

private slots:

    void on_btCall_clicked();

    void on_btHang_clicked();

    void call();

    void hangUp();

    void on_contactList_clicked(const QModelIndex &index);

private:
    Ui::Application *ui;
};

#endif // APPLICATION_H
