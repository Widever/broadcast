#ifndef RECEIVER_H
#define RECEIVER_H
#include <QCoreApplication>
#include <QObject>
#include <QTimer>
#include <QThread>
class QUdpSocket;

class Receiver : public QObject
{
    Q_OBJECT

public:
    explicit Receiver(QObject *parent = nullptr);
    void setMessage(const QString& newMessage);
    void setDelay(int newDelay);
    void setApp(QCoreApplication* newApp);
private slots:
    void processPendingDatagrams();
    void printMessage();
private:
    QCoreApplication* app;
    QUdpSocket *udpSocket = nullptr;
    QString message = "";
    QTimer timer;
    QThread timerThread;
signals:

};

#endif // RECEIVER_H
