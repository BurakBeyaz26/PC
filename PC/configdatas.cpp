#include "configdatas.h"

ConfigDatas * ConfigDatas::configdatas = NULL;
ConfigDatas::ConfigDatas(QObject *parent) : QObject(parent)
{
    createConfigifNotExists();
    readConfig();
}

void ConfigDatas::readConfig()
{
    QDir dir;
    QByteArray filecontent;
    QJsonObject contentObj;

    qDebug() << "dir.currentPath(): " << dir.currentPath();

    QFile file(dir.absolutePath()+"/config.json");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
           return;
    else
    {
        filecontent = file.readAll();
        contentObj = QJsonDocument::fromJson(filecontent).object();
        QString port = contentObj["serial_port"].toString();
        if(!port.isEmpty())
            setSerialPort(port);
    }
}

void ConfigDatas::createConfigifNotExists()
{
    QDir dir;
    dir.setPath(dir.absolutePath()+"/config.json");
    if (!dir.exists(dir.path()))
    {
        QFile file(dir.path());
        if(file.open(QIODevice::ReadWrite))
        {
            qDebug() << "Config file created.";
            QTextStream in(&file);
            QJsonObject obj;
            QJsonDocument doc;
            obj["serial_port"] = getSerialPort();
            doc.setObject(obj);
            in << doc.toJson();
        }
        else
        {
            qDebug() << "File Error: " << file.errorString();
            return;
        }

        file.close();
    }
    else
    {
        qDebug() << "Already Exists";
    }
}
void ConfigDatas::setSerialPort(QString serialport)
{
    m_port = serialport;
}
QString ConfigDatas::getSerialPort()
{
    return m_port;
}
