#include "serverdiscorverer.h"
#include <iostream>

int callback(Upnp_EventType EventType, void* Event, void* Cookie)
{
    ServerDiscoverer *self = ((ServerDiscoverer*)Cookie);
    switch(EventType)
    {
    case UPNP_DISCOVERY_SEARCH_RESULT:
        self->upnpEventReceived((Upnp_Discovery*)Event);
        break;
    case UPNP_DISCOVERY_SEARCH_TIMEOUT:
        std::cout << "timleout" << std::endl;
        emit self->finished();
    default:
        break;
    }
    return 0;
}

ServerDiscoverer::ServerDiscoverer(QObject *parent) :
    QObject(parent)
{
    QObject::connect(this, &ServerDiscoverer::__addIpThreadSafe, this, &ServerDiscoverer::__addIpThreadSafeImpl);
    UpnpInit(NULL, 49345);
    UpnpRegisterClient(callback, this, &m_clientHandle);
}

void ServerDiscoverer::startDiscovering()
{
    std::cout << UpnpSearchAsync(m_clientHandle, 10, "uuid:raspm-player-0.0.1", this) << std::endl;
}

void ServerDiscoverer::upnpEventReceived(Upnp_Discovery *event)
{
    if(strcmp(event->DeviceId, "uuid:raspm-player-0.0.1") == 0) {
        sockaddr *addr = ((sockaddr*)&(event->DestAddr));
        if(addr->sa_family == AF_INET)
        {
            sockaddr_in *addr_in = (sockaddr_in*) addr;
            char *ip = inet_ntoa(addr_in->sin_addr);
            emit __addIpThreadSafe(QString(ip));
        }
    }
}

void ServerDiscoverer::__addIpThreadSafeImpl(QString ip)
{
    if(!m_servers.contains(ip))
    {
        m_servers.insert(ip);
        std::cout << ip.toStdString() << std::endl;
        emit serverDiscovred(ip);
    }
}
