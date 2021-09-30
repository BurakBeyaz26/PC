#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>
#include <QSerialPort>
#include <QtSerialPort>
#include <QSerialPortInfo>
#include <QIODevice>
#include <QDebug>

#include "configdatas.h"

class SerialCommunication : public QObject
{
    Q_OBJECT
public:
    explicit SerialCommunication(QObject *parent = nullptr);
    ~SerialCommunication();
    void initSerial();
    void closeSerial();

    QSerialPort *serial;

public slots:
    void readyRead();
signals:
private:

};

#endif // SERIALCOMMUNICATION_H
