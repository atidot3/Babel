#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T11:00:43
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = Client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    udpsocket.cpp

HEADERS += \
    ISocket.hh \
    udpsocket.h
