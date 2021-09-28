#ifndef DATAMANAGEMENT_H
#define DATAMANAGEMENT_H

#include <QObject>
#include <QCoreApplication>
#include "serialcommunication.h"
#include "tcpsocketcommunication.h"
#include "log.h"

#include <QTimer>

class DataManagement : public QObject
{
    Q_OBJECT
public:
    explicit DataManagement(QObject *parent = nullptr);

    void SocketStart();
    void SerialStart();
    Log log;

    QString to_pis = "PassengerInformationSystem";
    bool pisconnected = false;
    bool CorrectSystemFlag;

public slots:
    void onConnected();
    void onDisconnected();
    void MessageReceived(QString message);


private:
    QTimer *identificationtimer = new QTimer();
    QTimer *socketcheck = new QTimer();

    bool isSocketOpened;
    bool isSocketalreadyOpened = false;
    QString ClientStatesStateText;

    void IdentificationSend(QString App,QString DeviceType,QString DeviceName);

    int SocketControlTimerValueinMsec;

    QString appname = "PC";
    QString Device_Type = "PC";
    QString Device_Name = "PC";
    QString deviceIP;
    QString Server_IP;

protected:

    TcpSocketCommunication *socketClient;
    SerialCommunication serialComm;

signals:

};

#endif // DATAMANAGEMENT_H
