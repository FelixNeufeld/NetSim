#include "process.h"
#include "package.h"
#include "../protocols/http.h"

void Process::httpGetRequest(const QString &url, const Port &sourcePort){
    Package httpRequestPackage("");
    HTTP::initHTTPRequest("GET",url,"HTTP/1.1",httpRequestPackage);

    openSocket(sourcePort);
    socket.addTCPHeader(httpRequestPackage);
}

void Process::openSocket(const Port &sourcePort){
    this->socket = Socket(sourcePort, Port(80));
}
