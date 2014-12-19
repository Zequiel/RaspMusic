#ifndef SERVERPRESENCENOTIFIER_H
#define SERVERPRESENCENOTIFIER_H

#include <QObject>
#include <QTimer>
#include <upnp/upnp.h>

class ServerPresenceNotifier
{
public:
    ServerPresenceNotifier();
    ~ServerPresenceNotifier();

private slots:
    void notify();

private:
    UpnpDevice_Handle m_device;
};

#endif // SERVERPRESENCENOTIFIER_H
