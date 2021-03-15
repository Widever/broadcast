#include <QCoreApplication>
#include <iostream>
#include "sender.h"
#include <QTextStream>
#include <QThread>
#include <windows.h>



int main(int argc, char *argv[])
{
    Q_UNUSED(argc)
    Q_UNUSED(argv)
    Sender* sender = new Sender();

    while(true){
        std::cout<<"Wait for input message (stringValue#space#delayValue or \"Quit\" for stop):\n";
        QString stringValue, delayValue;
        std::string stdStringValue, stdDelayValue;
        std::cin>>stdStringValue;
        stringValue = QString::fromStdString(stdStringValue);
        int delay = 0;

        if(stringValue!="Quit"){
            std::cin>>stdDelayValue;
            delayValue = QString::fromStdString(stdDelayValue);
            bool delayCheck = false;
            delay = delayValue.toInt(&delayCheck);

            if(!delayCheck){
                std::cout<<"invalid delayValue\n";
                delete sender;
                return 1;
            }
        }

        sender->setMessageData(stringValue);
        sender->setMessageDelay(delay);
        sender->broadcastDatagram();

        if(stringValue == "Quit"){
            break;
        }
    }
    delete sender;
    return 0;
}
