#ifndef SERVER_H
#define SERVER_H

#include "host.h"


class Server : public Host
{
private:
    QString m_domain;
    QString htmlFile;
public:
    Server(const NetworkCard &networkCard, const QString &domain);

    QString domain() const;

    void getRequest();
    void sendResponse();

    void receivePackage(Package &data) override;

    QString getHtmlFile()const;
};

#endif // SERVER_H
