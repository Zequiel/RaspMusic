#ifndef SERVERDISCORVRER_H
#define SERVERDISCORVRER_H

#include <QObject>
#include <upnp/upnp.h>
#include <QSet>

class ServerDiscoverer : public QObject
{
    Q_OBJECT
public:
    explicit ServerDiscoverer(QObject *parent = 0);

signals:
    void serverDiscovred(QString ip);
    void finished();
    void __addIpThreadSafe(QString ip);

public slots:
    void startDiscovering();
    void upnpEventReceived(Upnp_Discovery *event);
    void __addIpThreadSafeImpl(QString ip);

private:
    UpnpClient_Handle m_clientHandle;
    QSet<QString> m_servers;

};

#endif // SERVERDISCORVRER_H
