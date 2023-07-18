#ifndef TCP_H
#define TCP_H

#include "src/models/port.h"
#include "src/models/package.h"
#include <cstdint>
#include <QString>
#include <src/models/ipaddress.cpp>

/**
 * @brief The TCP class
 * @par Represents the Transport Control Protocol
 */
class TCP
{
public:
    /**
     * @brief initHeader
     * @param srcAdress
     * @param destAdress
     * @param sourcePort
     * @param destinationPort
     * @param seqNumber
     * @param ackNumber
     * @param ack
     * @param rst
     * @param syn
     * @param fin
     * @param window
     * @param data
     * @param dataLength
     * @par adds a TCP-Header to a package and calculates its checksum
     */
    static void initHeader(IPAddress srcAdress, IPAddress destAdress, Port sourcePort, Port destinationPort, qint32 seqNumber, qint32 ackNumber, bool ack,bool rst, bool syn, bool fin, qint16 window, Package data, qint16 dataLength);

private:
    static void setFlag(qint16* flags, bool set, qint16 position);
    static qint16 getTCPChecksum(qint8* sourceAddress, qint8* destinationAddress, qint16 sourcePort, qint16 destinationPort, qint32 seqNumber, qint32 ackNumber, qint16 flags,const char* data, qint16 dataLength);
};

#endif // TCP_H
