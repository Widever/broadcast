#include <QCoreApplication>
#include <iostream>
#include "sender.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    qDebug()<<"Hello world";
    Sender* sender = new Sender();
    return a.exec();
}
