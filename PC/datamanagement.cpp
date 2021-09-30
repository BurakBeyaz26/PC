#include "datamanagement.h"

DataManagement::DataManagement(QObject *parent) : QObject(parent)
{
    deviceIP = "192.168.152.128";
    Server_IP = "192.168.152.128";

//    IdentificationSend(appname,Device_Type,Device_Name);
//    connect(identificationtimer,&QTimer::timeout,this,[&]{IdentificationSend(appname,Device_Type,Device_Name);});

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
    Server_IP = QString("ws://").append(Server_IP);
    socketClient = new TcpSocketCommunication(Server_IP + QString::fromStdString(":4001"), Device_Type, deviceIP,Device_Name);
    connect(&socketClient -> m_webSocket, &QWebSocket::connected, this, &DataManagement::onConnected);
    connect(&socketClient -> m_webSocket, &QWebSocket::disconnected, this, &DataManagement::onDisconnected);
    connect(&socketClient -> m_webSocket, &QWebSocket::textMessageReceived, this, &DataManagement::MessageReceived);
}

void DataManagement::SerialStart()
{
    serialComm.initSerial();
    log.logWork("SerialStart","","","Seri haberleşme başlatıldı.");
    connect(serialComm.serial,&QSerialPort::readyRead,this,&DataManagement::SerialMessageReceived);
}

void DataManagement::processIncomingMessages(QString topic, QString message)
{
    if(topic == "ping")
    {
        sendSocketMessage("ping","");
    }
}
void DataManagement::onDisconnected()
{
    socketClient->isSocketClosed = true;
    log.logWork("onDisconnected","Socket bağlantısı koptu...");
}

void DataManagement::sendSocketMessage(QString topic, QString message)
{
    QJsonObject sendmessage;

    sendmessage["topic"] = topic;
    sendmessage["message"] = message;

    socketClient->sendTextMessage(topic,message);
}

void DataManagement::sendSerialMessage(QString message)
{
    serialComm.serial->write(message.toUtf8());
}

void DataManagement::IdentificationSend(QString App,QString DeviceType,QString DeviceName){

    qDebug() << "IdentificationSend";
    if(socketClient->isSocketClosed == false){


        QJsonObject identificationdatajson;

        identificationdatajson["App"] = App;
        identificationdatajson["DeviceType"] = DeviceType;
        identificationdatajson["DeviceName"] = DeviceName;
        identificationdatajson["SystemName"] = "PC";


        socketClient->sendTextMessage("identification/SystemControl","",identificationdatajson);
        identificationtimer->stop();
         qDebug() << "IdentificationSend Success...";
         log.logWork("IdentificationSend","true","","IdentificationSend Success...");
    }
    else{
        qDebug() << "IdentificationSend Fail...Socket not connected...";
        log.logWork("IdentificationSend","false","","IdentificationSend Fail...Socket not connected...");
        //connect(identificationtimer,SIGNAL(timeout()),this,SLOT(IdentificationSend));
        //connect(identificationtimer,&QTimer::timeout,this,[&]{IdentificationSend(appname,Device_Type,Device_Name);});
        identificationtimer->start(3000);
    }
}

void DataManagement::MessageReceived(QString message)
{
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    QJsonObject obj = doc.object();

    QString topic = obj["topic"].toString();
    QString incomingmessage = obj["message"].toString();

    qDebug() << "topic: " << topic << ", incomingmessage: " << incomingmessage;

    processIncomingMessages(topic,incomingmessage);
}

void DataManagement::processISerialMessages(QByteArray message)
{
    QStringList serialList;
    QString incomingmessage,topic;
    QString serialMessage = QString::fromUtf8(message);
    serialMessage.remove("\n");

    if(serialMessage.contains("/"))
    {
        serialList = serialMessage.split("/");
        topic = serialList.at(0);
        incomingmessage = serialList.at(1);
    }

    qDebug() << "serial : " << message;
    log.logWork("processISerialMessages","","",serialMessage);

    if(serialMessage == "Ping")
    {
        sendSerialMessage("Ping");
    }
    if(topic == "changeColor")
    {
        emit colorChanged(incomingmessage);
    }
}

void DataManagement::SerialMessageReceived()
{
    QByteArray data = serialComm.serial->readAll();
    processISerialMessages(data);
}
