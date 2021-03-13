#include "sender.h"
#include <QtNetwork>
#include <QtCore>

Sender::Sender(QObject *parent) : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    startBroadcasting();
    connect(&timer, &QTimer::timeout, this, &Sender::broadcastDatagram);
}

void Sender::startBroadcasting()
{
    timer.start(2000);
}

void Sender::broadcastDatagram()
{
    message = {QString("aaaaa%1").arg(messageNumber), 1000};
    qDebug()<<"send "<<message.data<<'\n';
    QByteArray datagram = QString(message.data+'&'+QString::number(message.delay)).toUtf8();
    udpSocket->writeDatagram(datagram, QHostAddress::Broadcast, 45454);
    ++messageNumber;
}
