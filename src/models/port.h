#ifndef PORT_H
#define PORT_H

#include <QString>

class Port
{
private:
    quint16 portNumber;
public:
    Port(quint16 portNumber) : portNumber(portNumber) {}
    quint16 getPortNumber() const {
        return portNumber;
    }
};

#endif // PORT_H
