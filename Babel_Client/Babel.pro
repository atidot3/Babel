QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    application.cpp \
    comclient.cpp \
    comserver.cpp

HEADERS  += mainwindow.h \
    application.h \
    ISound.h \
    comclient.h \
    comserver.h \
    ICommunicate.h

FORMS    += mainwindow.ui \
    application.ui

RESOURCES += \
    Assets.qrc

#LIBS += -L$$PWD/lib -lportaudio -lopus
