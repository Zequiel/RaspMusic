#include <QApplication>
#include <QQmlApplicationEngine>
#include "application.h"
#include "server.h"
#include "providers/youtubesearchclient.h"
#include "serverdiscorverer.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application appli;
    ServerDiscoverer discoverer;
    discoverer.startDiscovering();
    return app.exec();
}
