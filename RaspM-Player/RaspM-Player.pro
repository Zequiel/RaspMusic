#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T10:06:17
#
#-------------------------------------------------

QT       += core multimedia

QT       -= gui

TARGET = RaspM-Player
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++11

TEMPLATE = app


SOURCES += main.cpp \
    src/server.cpp \
    src/player.cpp \
    src/clientslistener.cpp \
    src/client.cpp \
    src/message/message.cpp \
    src/message/addtoplaylistmessage.cpp \
    src/messagehandler/messagehandler.cpp \
    src/messagehandler/addtoplaylisthandler.cpp \
    src/message/emptymessage.cpp \
    src/messagehandler/messagehandlerfactory.cpp

HEADERS += \
    src/server.h \
    src/player.h \
    src/clientslistener.h \
    src/client.h \
    src/message/message.h \
    src/message/addtoplaylistmessage.h \
    src/messagehandler/messagehandler.h \
    src/messagehandler/addtoplaylisthandler.h \
    src/message/emptymessage.h \
    src/messagehandler/messagehandlerfactory.h
