#ifndef CONFIGDATAS_H
#define CONFIGDATAS_H

#include <QObject>
#include <QFile>
#include <QDir>
#include <QJsonObject>
#include <QJsonDocument>
#include <QString>
#include <QTextStream>

class ConfigDatas : public QObject
{
    Q_OBJECT
public:
    explicit ConfigDatas(QObject *parent = nullptr);
    void readConfig();
    void createConfigifNotExists();

    void setSerialPort(QString serialport);
    QString getSerialPort();

    //static ConfigDatas* getInstance();
    static ConfigDatas* getInstance(){

        if (!configdatas)
        {
            configdatas = new ConfigDatas;
        }
        return configdatas;
    }

private:
    QString m_port = "/dev/pts/1";
    static ConfigDatas *configdatas;
signals:

};

#endif // CONFIGDATAS_H
