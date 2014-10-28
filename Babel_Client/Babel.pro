QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Babel
TEMPLATE = app

UI = ui
SRC = src
INC = inc
RSC = rsc
INCLUDEPATH += inc/

SOURCES += $$SRC/main.cpp\
    $$SRC/mainwindow.cpp \
    $$SRC/application.cpp \
    $$SRC/comclient.cpp \
    $$SRC/comserver.cpp

HEADERS  += $$INC/mainwindow.h \
    $$INC/application.h \
    $$INC/ISound.h \
    $$INC/comclient.h \
    $$INC/comserver.h \
    $$INC/ICommunicate.h

FORMS    += $$UI/mainwindow.ui \
    $$UI/application.ui

RESOURCES += \
    $$RSC/Assets.qrc

#LIBS += -L$$PWD/lib -lportaudio -lopus

release: DESTDIR = build/release
debug:   DESTDIR = build/debug

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
