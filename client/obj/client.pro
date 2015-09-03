QT += core network
QT -= gui

TEMPLATE = app

DESTDIR = ../bin
TARGET = client.bin

SOURCES += ../src/main.cpp \
    ../src/MyHttpClient.cpp

HEADERS += \
    ../src/MyHttpClient.h
