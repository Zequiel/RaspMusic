#include <QCoreApplication>
#include "src/server.h"
#include "src/clientslistener.h"
#include <iostream>
#include <easylogging++.h>
#include "src/mediacollection.h"

_INITIALIZE_EASYLOGGINGPP

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QCoreApplication::setApplicationName("Player");
    QCoreApplication::setOrganizationName("RaspMusic");
    Server server;
    ClientsListener listener(server);
    LOG(INFO) << "Server started !";
    return a.exec();
}
