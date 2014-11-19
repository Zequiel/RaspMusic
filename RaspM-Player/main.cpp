#include <QCoreApplication>
#include "src/server.h"
#include "src/clientslistener.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server server;
    ClientsListener listener(server);
    std::cout << "Server started !" << std::endl;
    return a.exec();
}
