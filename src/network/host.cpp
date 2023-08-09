#include "host.h"
#include "router.h"
#include "src/management/packagedatabase.h"

QMap<Port, Process> Host::getProcessTable() const
{
    return processTable;
}

QMap<IPAddress, MACAddress> Host::getHostTable() const
{
    return hostTable;
}

QMap<QString, IPAddress> Host::getDomainTable() const
{
    return domainTable;
}

NetworkCard Host::getNetworkCard() const
{
    return networkCard;
}

Host::Host(const NetworkCard &networkCard) :
    networkCard(networkCard)
{
    Process http(this,80);
    Process dns(this, 53);
    processTable[http.getSocket().getSourcePort().getPortNumber()] = http;
    processTable[dns.getSocket().getSourcePort().getPortNumber()] = dns;
}

Router* Host::getRouterByMACAddress(MACAddress destinationAddress){
    return this->cables[destinationAddress];
}

void Host::sendPackage(Package &data, MACAddress destinationAddress){
    cables[destinationAddress]->receivePackage(data);
}

void Host::addIPAddress(const IPAddress &ipAddress, const MACAddress &macAddress)
{
    hostTable[ipAddress] = macAddress;
}

void Host::addMACAddress(const MACAddress &macAddress, Router *router)
{
    cables[macAddress] = router;
}

void Host::addDomain(const QString &domain, const IPAddress &ipAddress)
{
    domainTable[domain] = ipAddress;
}
