#include "serialcommunication.h"

SerialCommunication::SerialCommunication(QObject *parent) : QObject(parent)
{
    serial = new QSerialPort(this);
}

SerialCommunication::~SerialCommunication()
{
    closeSerial();
}

void SerialCommunication::initSerial()
{
    ConfigDatas *config = ConfigDatas::getInstance();
    QString port =  config->getSerialPort();
    qDebug() << "port: " << port;

    serial->setPortName(port);
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "Connected";
        connect(serial, &QSerialPort::readyRead, this,&SerialCommunication::readyRead);
    }
    else
    {
        qCritical() << "ERROR: " << serial->errorString();
    }
}

void SerialCommunication::closeSerial()
{
     if(serial->isOpen())
        serial->close();
}
void SerialCommunication::readyRead()
{

//    QByteArray data = serial->readAll();
//    qDebug() << "serial : " << data;

}
