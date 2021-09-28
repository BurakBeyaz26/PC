#ifndef TCPSOCKETCOMMUNICATION_H
#define TCPSOCKETCOMMUNICATION_H

#include <QWebSocket>

class TcpSocketCommunication : public QObject
{
    Q_OBJECT
public:
    explicit TcpSocketCommunication(const QUrl &url, const QString &deviceType, const QString &deviceIPAdress, const QString &deviceName);
    void sendTextMessage(QString topic, QString message, QJsonObject messagejson);
    QWebSocket m_webSocket;
    QString s_deviceName;
    bool isSocketClosed;
    QUrl m_url;
    void open(QUrl url, QString deviceType, QString deviceIPAddress, QString deviceName);
    QString s_deviceType;
    QString deviceIPAddress;
    void close();
    void sendBuffer(QByteArray message);

public Q_SLOTS:
    void onConnected();

private Q_SLOTS:
    void onTextMessageReceived(QString message);
    void onTestMessage(QString message);


private:
    bool m_debug;
    void closed();
};


#endif // TCPSOCKETCOMMUNICATION_H
