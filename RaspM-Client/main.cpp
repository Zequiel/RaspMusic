#include <QApplication>
#include <QQmlApplicationEngine>
#include "application.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application appli;


    return app.exec();
}
