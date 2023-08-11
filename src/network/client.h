#ifndef CLIENT_H
#define CLIENT_H

#include "host.h"

namespace NetSim {
class Client;
}

class Client : public Host {
public:
  Client(const NetworkCard &networkCard);

  void execDomainResolution(const QString &domain);

  void execHandShake(const IPAddress &address);

  void execHTTPRequest(const IPAddress &address, const QString &uri);

  void execCloseConnection(const IPAddress &address);

  void receivePackage(Package data) override;
};

#endif // CLIENT_H
