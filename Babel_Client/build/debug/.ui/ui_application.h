/********************************************************************************
** Form generated from reading UI file 'application.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPLICATION_H
#define UI_APPLICATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Application
{
public:
    QLabel *label;
    QListWidget *contactList;
    QPushButton *btCall;
    QPushButton *btHang;
    QLabel *tvStatus;

    void setupUi(QWidget *Application)
    {
        if (Application->objectName().isEmpty())
            Application->setObjectName(QStringLiteral("Application"));
        Application->resize(283, 489);
        Application->setMinimumSize(QSize(283, 489));
        Application->setMaximumSize(QSize(283, 489));
        QIcon icon;
        icon.addFile(QStringLiteral(":/call.png"), QSize(), QIcon::Normal, QIcon::Off);
        Application->setWindowIcon(icon);
        label = new QLabel(Application);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 40, 191, 16));
        contactList = new QListWidget(Application);
        new QListWidgetItem(contactList);
        new QListWidgetItem(contactList);
        new QListWidgetItem(contactList);
        contactList->setObjectName(QStringLiteral("contactList"));
        contactList->setGeometry(QRect(10, 60, 256, 311));
        btCall = new QPushButton(Application);
        btCall->setObjectName(QStringLiteral("btCall"));
        btCall->setEnabled(false);
        btCall->setGeometry(QRect(20, 430, 101, 41));
        btCall->setIcon(icon);
        btHang = new QPushButton(Application);
        btHang->setObjectName(QStringLiteral("btHang"));
        btHang->setEnabled(false);
        btHang->setGeometry(QRect(150, 430, 101, 41));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/hangup.png"), QSize(), QIcon::Normal, QIcon::Off);
        btHang->setIcon(icon1);
        tvStatus = new QLabel(Application);
        tvStatus->setObjectName(QStringLiteral("tvStatus"));
        tvStatus->setGeometry(QRect(20, 380, 241, 31));

        retranslateUi(Application);

        QMetaObject::connectSlotsByName(Application);
    } // setupUi

    void retranslateUi(QWidget *Application)
    {
        Application->setWindowTitle(QApplication::translate("Application", "Babel - 1.0.0", 0));
        label->setText(QApplication::translate("Application", "Liste des personnes connect\303\251s :", 0));

        const bool __sortingEnabled = contactList->isSortingEnabled();
        contactList->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = contactList->item(0);
        ___qlistwidgetitem->setText(QApplication::translate("Application", "Tolo", 0));
        QListWidgetItem *___qlistwidgetitem1 = contactList->item(1);
        ___qlistwidgetitem1->setText(QApplication::translate("Application", "Carr\303\251", 0));
        QListWidgetItem *___qlistwidgetitem2 = contactList->item(2);
        ___qlistwidgetitem2->setText(QApplication::translate("Application", "Bottom", 0));
        contactList->setSortingEnabled(__sortingEnabled);

        btCall->setText(QApplication::translate("Application", "Appeler", 0));
        btHang->setText(QApplication::translate("Application", "Raccrocher", 0));
        tvStatus->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Application: public Ui_Application {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPLICATION_H
