TEMPLATE = app

QT += qml quick widgets

SOURCES += main.cpp \
    server.cpp \
    application.cpp \
    providers/youtubesearchclient.cpp \
    providers/searchresult.cpp \
    serverdiscorverer.cpp

RESOURCES += qml.qrc
QMAKE_CXXFLAGS += -std=c++11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    server.h \
    application.h \
    providers/youtubesearchclient.h \
    providers/searchresult.h \
    serverdiscorverer.h

unix|win32: LIBS += -lupnp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../Common/release/ -lCommon
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../Common/debug/ -lCommon
else:unix: LIBS += -L$$OUT_PWD/../Common/ -lCommon

INCLUDEPATH += $$PWD/../Common
DEPENDPATH += $$PWD/../Common
