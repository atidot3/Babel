#include "ui.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

Ui::Ui(QWidget* parent, Qt::WFlags flags)
: QWidget(parent, flags)
{
    QVBoxLayout* main	= new QVBoxLayout(this);
    QGridLayout* top	= new QGridLayout;

    QLabel* label	= new QLabel("Server:", this);
    top->addWidget(label, 0, 0);
    main->addLayout(top);
    setLayout(main);
}

Ui::~Ui()
{

}
