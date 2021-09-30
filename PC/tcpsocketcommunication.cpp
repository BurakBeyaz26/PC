#include "tcpsocketcommunication.h"
#include <QtCore/QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

QT_USE_NAMESPACE

TcpSocketCommunication::TcpSocketCommunication(const QUrl &url, const QString &deviceType, const QString &deviceIPAddress, const QString &deviceName) :
    m_url(url),
    s_deviceType(deviceType),
    deviceIPAddress(deviceIPAddress),
    s_deviceName(deviceName)

{
    isSocketClosed = false;
    qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &TcpSocketCommunication::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &TcpSocketCommunication::closed);

    open(QUrl(url), deviceType,deviceIPAddress,deviceName);
}

void TcpSocketCommunication::open(QUrl url, QString deviceType, QString deviceIPAddress,QString deviceName)
{
    QNetworkRequest request(url);
    request.setRawHeader("x-request-device", deviceType.toUtf8());
    request.setRawHeader("request-deviceip", deviceIPAddress.toUtf8());
    request.setRawHeader("x-request-deviceName",deviceName.toUtf8());
    qDebug() << "device adress = " << deviceIPAddress.toUtf8();
    m_webSocket.open(request);
}

void TcpSocketCommunication::onConnected()
{
    qDebug() << "WebSocket connected";
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &TcpSocketCommunication::onTextMessageReceived);
    isSocketClosed = false;

}

void TcpSocketCommunication::sendTextMessage(QString topic, QString message, QJsonObject messagejson)
{
    QJsonObject jsonmessage;;
    if(topic == "identification/SystemControl"){
        jsonmessage["topic"] = topic;
        jsonmessage["message"] = messagejson;

        QJsonDocument doc(jsonmessage);

        m_webSocket.sendTextMessage(doc.toJson());
    }
    else{
        jsonmessage["topic"] = topic;
        jsonmessage["message"] = messagejson;
        QJsonDocument doc(jsonmessage);

        if(isSocketClosed) open(m_url, s_deviceType,deviceIPAddress,s_deviceName);
        m_webSocket.sendTextMessage(doc.toJson());
    }
}

void TcpSocketCommunication::sendBuffer(QByteArray message){
    if(isSocketClosed) open(m_url, s_deviceType,deviceIPAddress,s_deviceName);
    m_webSocket.sendBinaryMessage(message);

}

void TcpSocketCommunication::onTestMessage(QString message)
{
    qDebug() << "Message received:" << message;
}

void TcpSocketCommunication::onTextMessageReceived(QString data)
{
   //qDebug() << "ComingData : " << data;
}

void TcpSocketCommunication::close()
{
    m_webSocket.close();
}

void TcpSocketCommunication::closed()
{
    isSocketClosed = true;
}
