#ifndef SERVER_H
#define SERVER_H

#include "host.h"


class Server : public Host
{
public:
    Server();

    void getRequest();
    void sendResponse();
};

#endif // SERVER_H
