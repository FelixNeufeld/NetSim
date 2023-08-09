#ifndef PROCESS_H
#define PROCESS_H

#include "src/network/socket.h"
#include "ipaddress.h"

#include <QString>

class Host;

class Process
{
public:
    Process(){};

    Process(Host* host, const Port &destinationPort);

    Socket getSocket();

    void openSocket(const Port &destinationPort);

    Package getHTTPRequest(const QString &uri);

    //TODO IMPLEMENT
    Package getHTTPResponse(IPAddress destination);

    //TODO SERVER SIDE
    Package& getHandShakePackage(const QString &url, bool initiate, bool client);

private:
    Socket socket;
    Host* host;
};

#endif // PROCESS_H
