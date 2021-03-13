#ifndef SENDER_H
#define SENDER_H
#include <QString>
#include <QTimer>
#include <QObject>

class QUdpSocket;

struct Message{
    QString data = "";
    int delay = 0;
};

class Sender : public QObject
{
    Q_OBJECT
public:
    Sender(QObject* parent = nullptr);
    void startBroadcasting();
public slots:
    void broadcastDatagram();
private:
    Message message;
    QUdpSocket *udpSocket = nullptr;
    QTimer timer;
    int messageNumber = 0;
};

#endif // SENDER_H
