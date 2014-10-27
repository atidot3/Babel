QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    application.cpp

HEADERS  += mainwindow.h \
    application.h

FORMS    += mainwindow.ui \
    application.ui

RESOURCES += \
    Assets.qrc

LIBS += -L$$PWD/lib -lportaudio -lopus
