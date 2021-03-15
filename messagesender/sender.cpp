#include "sender.h"
#include <QtNetwork>
#include <QtCore>

Sender::Sender(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

void Sender::setMessageData(const QString &messageData)
{
    message.data = messageData;
}

void Sender::setMessageDelay(int messageDelay)
{
    if(messageDelay<250) messageDelay = 250;
    if(messageDelay>2000) messageDelay = 2000;
    message.delay = messageDelay;
}

void Sender::broadcastDatagram()
{
    QByteArray datagram = QString(message.data+'&'+QString::number(message.delay)).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    ++messageNumber;
}
