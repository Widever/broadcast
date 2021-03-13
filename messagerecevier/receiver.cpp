#include "receiver.h"
#include <QtNetwork>

Receiver::Receiver(QObject *parent) : QObject(parent), message(QString("Hey, I am here."))
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
    timer.start(500);
    connect(udpSocket, &QUdpSocket::readyRead,
            this, &Receiver::processPendingDatagrams);
    connect(&timer, &QTimer::timeout, this, &Receiver::printMessage);
}

void Receiver::setMessage(const QString &newMessage)
{
    message = newMessage;
}

void Receiver::setDelay(int newDelay)
{
    timer.start(newDelay);
}

void Receiver::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        //qDebug()<<"receive "<<datagram.constData()<<'\n';
        QString receivedData = datagram.constData();
        int delimIndex = receivedData.lastIndexOf('&');
        QString newMessage = receivedData.mid(0, delimIndex-1);
        int newDelay = receivedData.mid(delimIndex+1).toInt();
        qDebug()<<"newDelay"<<newDelay<<"newMessage"<<newMessage;
        setDelay(newDelay);
        setMessage(newMessage);
    }
}

void Receiver::printMessage(){
    qDebug()<<"print message"<<message;
}
