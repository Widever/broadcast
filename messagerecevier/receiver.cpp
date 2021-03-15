#include "receiver.h"
#include <QtNetwork>
#include <iostream>
#include <QFuture>
#include <QThread>
#include <QtConcurrent>

Receiver::Receiver(QObject *parent) : QObject(parent), message(QString("Hey, I am here."))
{

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(45454, QUdpSocket::ShareAddress);
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

void Receiver::setApp(QCoreApplication *newApp)
{
    app = newApp;
}

void Receiver::processPendingDatagrams()
{
    QByteArray datagram;
    while (udpSocket->hasPendingDatagrams()) {
        datagram.resize(int(udpSocket->pendingDatagramSize()));
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QString receivedData = datagram.constData();
        int delimIndex = receivedData.lastIndexOf('&');
        QString newMessage = receivedData.mid(0, delimIndex);
        int newDelay = receivedData.mid(delimIndex+1).toInt();
        setDelay(newDelay);
        if(newMessage=="Quit"){
            timer.stop();
            std::cout<<"Quit";
            app->exit(0);
            delete this;
            return;
        }
        setMessage(newMessage);
    }
}

void Receiver::printMessage(){
    std::cout<<message.toStdString()<<'\n';
}
