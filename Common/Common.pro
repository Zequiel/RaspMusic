#-------------------------------------------------
#
# Project created by QtCreator 2014-11-19T09:56:35
#
#-------------------------------------------------

QT       -= gui

TARGET = Common
TEMPLATE = lib

DEFINES += COMMON_LIBRARY

SOURCES += common.cpp \
    message/message.cpp \
    message/addtoplaylistmessage.cpp \
    message/emptymessage.cpp \

HEADERS += common.h\
        common_global.h \
    message/message.h \
    message/emptymessage.h \
    message/addtoplaylistmessage.h \

QMAKE_CXXFLAGS += -std=c++11

unix {
    target.path = /usr/lib
    INSTALLS += target
}
