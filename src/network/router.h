#ifndef ROUTER_H
#define ROUTER_H

#include <QString>
#include <QStack>
#include <QHash>
#include "host.h"
#include "natentry.h"
#include "src/models/ipaddress.h"
#include "src/network/networkcard.h"

class Host;

class Router
{
private:
    QMap<IPAddress, MACAddress> macTable;
    QMap<MACAddress, Router*> routerCable;
    QMap<MACAddress, Host*> hostCable;
    QMap<Port,NATEntry> portToNAT;
    QMap<NATEntry, Port> natToPort;
    NetworkCard networkCard;
    IPAddress globalIpAddress;
public:
    Router();

    void addDomain(const QString &domain, const IPAddress &ipAddress);
    bool initializeServerConnection();
    void receivePackage(Package data);
    IPAddress getGlobalIpAddress() const;
    NetworkCard getNetworkCard() const;
    void addIPAddress(const IPAddress &ipAddress, const MACAddress &macaddress);
    void addMACAddress(const MACAddress &macAddress, Router *router);
    void addMACAddress(const MACAddress &macAddress, Host *host);
};

#endif // ROUTER_H
