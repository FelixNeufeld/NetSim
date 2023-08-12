#include "tcpconnectionclosestrategy.h"
#include "src/network/cablenotfoundexception.h"
#include "src/network/router.h"
#include "src/protocols/headerutil.h"

using namespace NetSim;

TCPConnectionCloseStrategy::~TCPConnectionCloseStrategy() {}

void TCPConnectionCloseStrategy::handle(Package package, Host *host) {
  Process httpProcess;
  try {
    httpProcess = host->getProcessByName("HTTP");
  } catch (const std::runtime_error &re) {
    qDebug() << "Process HTTP not found in: Server::receivePackage "
                "connection close";
    return;
  }

  httpProcess.getSocket().setDestinationPort(
      HeaderUtil::getPortAsPort(package, true));

  Package finAckPackage = httpProcess.generateCloseConnectionPackage(
      HeaderUtil::getIPAddressAsIPAddress(package, true), false, false);

  MACAddress routerMAC = host->hostTable().value(
      HeaderUtil::getIPAddressAsIPAddress(package, true));
  Router *router;
  try {
    router = host->getRouterByMACAddress(routerMAC);
  } catch (const CableNotFoundException &cnfe) {
    qDebug()
        << cnfe.errorMessage()
        << " in Server::receivePackage creating the closeConnection Response";
    return;
  }

  if (router == nullptr) {
    qDebug() << "Router is nullptr in Server::receivePackage";
    return;
  }

  qInfo() << "Server: " << host->networkCard().networkAddress().toString()
          << " sends FINACK Package to router: "
          << router->networkCard().physicalAddress().toString();
  router->receivePackage(finAckPackage);
}
