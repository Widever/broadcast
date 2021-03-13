#include <QCoreApplication>
#include "receiver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Receiver* receiver = new Receiver();
    return a.exec();
}
