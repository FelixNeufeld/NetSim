#include "clientwidget.h"

ClientWidget::ClientWidget(Client* client, QWidget *parent)
    : QWidget{parent}, m_client{client}
{
    //Erstelle die Widgets
    m_button = new QPushButton(this);
    m_ipLabel = new QLabel(this);
    m_macLabel = new QLabel(this);

    //Set the Icon
    m_button->setIcon(QIcon(":/client.svg"));
    m_button->setIconSize(QSize(64, 64));

    m_ipLabel->setText("IP-Adresse: " + m_client->getNetworkCard().getNetworkAddress().getAddressAsDecString());
    m_macLabel->setText("MAC-Adresse: " + m_client->getNetworkCard().getPhysicalAddress().getAddressAsString());

}
