#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QTimer>
class QUdpSocket;

class Receiver : public QObject
{
    Q_OBJECT
public:
    explicit Receiver(QObject *parent = nullptr);
    void setMessage(const QString& newMessage);
    void setDelay(int newDelay);
private slots:
    void processPendingDatagrams();
    void printMessage();
private:
    QUdpSocket *udpSocket = nullptr;
    QString message = "";
    QTimer timer;
signals:

};

#endif // RECEIVER_H
