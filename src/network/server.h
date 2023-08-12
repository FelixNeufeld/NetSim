#ifndef SERVER_H
#define SERVER_H

#include "host.h"

namespace NetSim {

class Server : public Host {
public:
  Server() = default;
  Server(const NetworkCard &networkCard, const QString &domain,
         const QString &html);

  QString domain() const;

  void receivePackage(Package data) override;

  QString htmlFile() const;

private:
  QString m_domain{};

  QString m_htmlFile{};
};
} // namespace NetSim

#endif // SERVER_H
