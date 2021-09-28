#include "datamanagement.h"

DataManagement::DataManagement(QObject *parent) : QObject(parent)
{
    deviceIP = "192.168.152.128";
    Server_IP = "192.168.152.128";

}
void DataManagement::onConnected()
{
    qDebug() << "Socket 1 bağlandı..";
    socketClient->isSocketClosed = false;
    SocketControlTimerValueinMsec = 3000;
    socketcheck->stop();
    socketcheck -> start(SocketControlTimerValueinMsec);
    log.logWork("onConnected","Socket yeniden bağlandı...");

    IdentificationSend(appname,Device_Type,Device_Name);


}
void DataManagement::SocketStart()
{
    socketClient = new TcpSocketCommunication(Server_IP + QString::fromStdString(":4001"), Device_Type, deviceIP,Device_Name);
    connect(&socketClient -> m_webSocket, &QWebSocket::connected, this, &DataManagement::onConnected);
    connect(&socketClient -> m_webSocket, &QWebSocket::disconnected, this, &DataManagement::onDisconnected);
    connect(&socketClient -> m_webSocket, &QWebSocket::textMessageReceived, this, &DataManagement::MessageReceived);
}

void DataManagement::SerialStart()
{
    serialComm.initSerial();
    log.logWork("SerialStart","","","Seri haberleşme başlatıldı.");
}
void DataManagement::onDisconnected()
{
    socketClient->isSocketClosed = true;
    log.logWork("onDisconnected","Socket bağlantısı koptu...");
}

void DataManagement::IdentificationSend(QString App,QString DeviceType,QString DeviceName){

    qDebug() << "IdentificationSend";
    if(socketClient->isSocketClosed == false){


        QJsonObject identificationdatajson;

        identificationdatajson["App"] = App;
        identificationdatajson["DeviceType"] = DeviceType;
        identificationdatajson["DeviceName"] = DeviceName;


        socketClient->sendTextMessage("identification/SystemControl","",identificationdatajson);
        identificationtimer->stop();
         qDebug() << "IdentificationSend Success...";
         log.logWork("IdentificationSend","true","","IdentificationSend Success...");
    }
    else{
        qDebug() << "IdentificationSend Fail...Socket not connected...";
        log.logWork("IdentificationSend","false","","IdentificationSend Fail...Socket not connected...");
        connect(identificationtimer,SIGNAL(timeout()),this,SLOT(IdentificationSend));
        identificationtimer->start(3000);
    }
}

void DataManagement::MessageReceived(QString message)
{
    qDebug() << "MessageReceived: " << message;
}
