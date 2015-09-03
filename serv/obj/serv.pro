QT += core network
QT -= gui

TEMPLATE = app

DESTDIR = ../bin
TARGET = serv.bin

SOURCES += ../src/main.cpp \
    ../src/MyHttpServer.cpp

HEADERS += \
    ../src/MyHttpServer.h
