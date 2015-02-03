#include <QApplication>
#include <QQmlApplicationEngine>
#include "application.h"
#include "server.h"
#include "providers/youtubesearchclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application appli;
    return app.exec();
}
