#include <QCoreApplication>
#include "receiver.h"
#include <QFuture>
#include <QThread>
#include <QtConcurrent>

int main(int argc, char *argv[])
{
    QCoreApplication qapplication(argc, argv);
    Receiver* receiver = new Receiver();
    receiver->setApp(&qapplication);
    receiver->setDelay(500);

    return qapplication.exec();
}
