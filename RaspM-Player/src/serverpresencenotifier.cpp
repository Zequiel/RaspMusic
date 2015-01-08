#include "serverpresencenotifier.h"
#include <iostream>
#include <QThread>

void handleSearchResult(Upnp_Discovery *event);
extern "C" int UpnpCallback(Upnp_EventType EventType, void *Event, void *Cookie)
{
    return 0;
}

ServerPresenceNotifier::ServerPresenceNotifier()
{
    const char* description = "<?xml version=\"1.0\"?> \
            <root xmlns=\"urn:schemas-upnp-org:device-1-0\"> \
            <specVersion> \
            <major>1</major> \
            <minor>0</minor> \
            </specVersion> \
            <device> \
            <deviceType>urn:schemas-upnp-org:device:raspm-player:1</deviceType> \
            <friendlyName>RaspMusic Server Player</friendlyName> \
            <manufacturer>RaspM</manufacturer> \
            <manufacturerURL>https://github.com/Zequiel/RaspMusic</manufacturerURL> \
            <modelDescription>RaspMusic Server Player V0.0.1</modelDescription> \
            <modelName>RaspM</modelName> \
            <modelNumber>1.0</modelNumber> \
            <modelURL>https://github.com/Zequiel/RaspMusic</modelURL> \
            <serialNumber>1654874561564</serialNumber> \
            <UDN>uuid:raspm-player-0.0.1</UDN> \
            <UPC>00000001</UPC> \
            <serviceList> \
            </serviceList> \
            <presentationURL>https://github.com/Zequiel/RaspMusic</presentationURL> \
            </device> \
            </root> \
            ";
    int res;
    if(UpnpInit(NULL, 49345) != UPNP_E_SUCCESS)
    {
        std::cout << "init error" << std::endl;
    }
    if((res = UpnpRegisterRootDevice2(Upnp_DescType::UPNPREG_BUF_DESC, description, strlen(description), 1, &UpnpCallback, "device", &m_device)) != UPNP_E_SUCCESS)
    {
        std::cout << "device init error" << res <<std::endl;
    }
    UpnpSendAdvertisement(m_device, 5);
}

ServerPresenceNotifier::~ServerPresenceNotifier()
{
    UpnpFinish();
}

void ServerPresenceNotifier::notify()
{

}
