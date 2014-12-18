#include <QApplication>
#include <QQmlApplicationEngine>
#include "application.h"
#include "server.h"
#include "providers/youtubesearchclient.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Application appli;
    YoutubeSearchClient client;
    client.search("coucou");

    return app.exec();
}
