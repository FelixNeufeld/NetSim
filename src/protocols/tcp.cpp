#include "tcp.h"
#include "headerAttribute.h"


void TCP::initHeader(const IPAddress &srcAdress, const IPAddress &destAdress, const Port &sourcePort, const Port &destinationPort, quint32 seqNumber, quint32 ackNumber, bool ack, bool rst, bool syn, bool fin, quint16 window, Package& data, quint16 dataLength){
    HeaderAttribute srcPort("Source Port",16,sourcePort.getPortNumber());
    HeaderAttribute dstPort("Destination Port",16,destinationPort.getPortNumber());
    HeaderAttribute sequenceNumber("Sequence number",32,seqNumber);
    HeaderAttribute acknowledgementNumber("Acknowledgment number",32,ackNumber);

    //Sets the flags for the TCP Header Urgent and Push flag are always 0
    quint16 flags = 0x0000000000000000;
    setFlag(&flags,ack,11);
    setFlag(&flags,rst,13);
    setFlag(&flags,syn,14);
    setFlag(&flags,fin,15);

    //Data-Offset is always 0, because we don't use the options TCP provides in this project
    HeaderAttribute flag("Flags",16,flags);
    HeaderAttribute windowSize("window",16,window);

    HeaderAttribute checksum("TCP Checksum",16,
                                            getTCPChecksum(srcAdress.getAddressAsArray(),
                                            destAdress.getAddressAsArray(),
                                            sourcePort.getPortNumber(),
                                            destinationPort.getPortNumber(),
                                            seqNumber,
                                            ackNumber,
                                            flags,
                                            data.getData().toStdString().c_str(),
                                            dataLength));

    //The urgent pointer is always 0 in our case
    quint16 urgent_pointer = 0b0000000000000000;
    HeaderAttribute urgentPointer("Urgent Pointer",16,urgent_pointer);
    HeaderAttribute options("Options",static_cast<quint8>(0),static_cast<quint8>(0));

    Header tcpHeader;
    tcpHeader.setHeaderType(HeaderType::TCP);
    tcpHeader.addHeaderAttribute(srcPort);
    tcpHeader.addHeaderAttribute(dstPort);
    tcpHeader.addHeaderAttribute(sequenceNumber);
    tcpHeader.addHeaderAttribute(acknowledgementNumber);
    tcpHeader.addHeaderAttribute(flag);
    tcpHeader.addHeaderAttribute(windowSize);
    tcpHeader.addHeaderAttribute(checksum);
    tcpHeader.addHeaderAttribute(urgentPointer);
    tcpHeader.addHeaderAttribute(options);

    data.addHeader(tcpHeader);
}


void TCP::setFlag(quint16* flags, bool set, quint16 position){
    if (set) {
        // sets the bit at position
        *flags |= (1 << position);
    } else {
        // deletes the bit at position
        *flags &= ~(1 << position);
    }
}

quint16 TCP::getTCPChecksum(const QVector<quint8> &sourceAddress, const QVector<quint8> &destinationAddress, quint16 sourcePort, quint16 destinationPort, quint32 seqNumber, quint32 ackNumber, quint16 flags,const char* data, quint16 dataLength) {
    // TCP Pseudo Header
    quint32 pseudoHeader = 0;

    // Splitting the source IP-Address into 2 16-bit parts with correct byte order
    quint16 sourceIPAdressPart1 = (sourceAddress[0] << 8) | (sourceAddress[1] & 0xFF);
    quint16 sourceIPAdressPart2 = (sourceAddress[2] << 8) | (sourceAddress[3] & 0xFF);

    // Splitting the destination IP-Address into 2 16-bit parts with correct byte order
    quint16 destinationIPAdressPart1 = (destinationAddress[0] << 8) | (destinationAddress[1] & 0xFF);
    quint16 destinationIPAdressPart2 = (destinationAddress[2] << 8) | (destinationAddress[3] & 0xFF);

    pseudoHeader += sourceIPAdressPart1;
    pseudoHeader += sourceIPAdressPart2;
    pseudoHeader += destinationIPAdressPart1;
    pseudoHeader += destinationIPAdressPart2;
    pseudoHeader += 6; // IP protocol field for TCP is 6
    pseudoHeader += dataLength;

    quint16 checksum = 0;
    //Adding the pseudo Header to the checksum and handling the possible overflow
    while (pseudoHeader >> 16){
        pseudoHeader = (pseudoHeader & 0xFFFF) + (pseudoHeader >> 16);
    }
    checksum += pseudoHeader;

    //Adding the TCP-Header data
    checksum += sourcePort;
    checksum += destinationPort;
    checksum += seqNumber;
    checksum += ackNumber;
    checksum += flags;

    //Adding the TCP Data
    for (int i = 0; i < dataLength; i += 2) {
        quint16 dataWord = (data[i] << 8) | (data[i + 1] & 0xFF);
        checksum += dataWord;
        if (checksum >> 16)
            checksum = (checksum & 0xFFFF) + (checksum >> 16);
    }

    qInfo() << "TCP Checksum: " << ~checksum;
    return ~checksum;
}
