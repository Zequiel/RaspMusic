#-------------------------------------------------
#
# Project created by QtCreator 2014-11-05T10:06:17
#
#-------------------------------------------------

QT       += core multimedia sql

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
    src/messagehandler/addtoplaylisthandler.cpp \
    src/messagehandler/messagehandler.cpp \
    src/messagehandler/messagehandlerfactory.cpp \
    src/mediacollection.cpp \
    src/requests/addtoplaylistrequest.cpp \
    src/messagehandler/setstatehandler.cpp

HEADERS += \
    src/server.h \
    src/player.h \
    src/clientslistener.h \
    src/client.h \
    src/messagehandler/addtoplaylisthandler.h \
    src/messagehandler/messagehandler.h \
    src/messagehandler/messagehandlerfactory.h \
    src/mediacollection.h \
    src/requests/addtoplaylistrequest.h \
    src/messagehandler/setstatehandler.h

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Common/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Common/debug/ -lCommon
else:unix: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
INCLUDEPATH += ../libs/
DEPENDPATH += $$PWD/../Common

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Common/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Common/debug/ -lCommon
else:unix: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common
