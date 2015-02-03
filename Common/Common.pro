#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T09:56:35
#
#-------------------------------------------------

QT       -= gui
QT       += network

TARGET = Common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

SOURCES += common.cpp \
    message/message.cpp \
    message/addtoplaylistmessage.cpp \
    message/emptymessage.cpp \
    messagereaderwriter.cpp \
    message/setstatemessage.cpp \
    message/currentsourcemessage.cpp \
    message/getcurrentsourcemessage.cpp

HEADERS += common.h\
        common_global.h \
    message/message.h \
    message/emptymessage.h \
    message/addtoplaylistmessage.h \
    messagereaderwriter.h \
    message/setstatemessage.h \
    message/currentsourcemessage.h \
    message/getcurrentsourcemessage.h

QMAKE_CXXFLAGS += -std=c++11
CONFIG += staticlib

unix {
    target.path = /usr/lib
    INSTALLS += target
}
