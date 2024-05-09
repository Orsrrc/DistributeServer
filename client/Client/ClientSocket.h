#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <QObject>
#include <QDebug>
#include <QString>
#include <QAbstractSocket>
#include <QTcpSocket>
#include <QHostAddress>
#include <QtTypes>
#include <QIODevice>
#include <QUdpSocket>
#include "common.h"



class Network
{
public:
    explicit Network(QObject *parent = 0);
    ~Network();


    int createSocket(QObject* parent , int protocol = PROTOCOL_TCP);

    //UDP

    int sendByUdp(QString Username, QString Password, QHostAddress ServerAddress, quint16 ServerPort);
    int UdpBind(QHostAddress ServerAddress, quint16 ServerPort);

   //TCP
    int TcpConnect( QString ServerAddress, quint16 ServerPort = 9800);
     int sendByTcp(QString Username, QString Password);

    int receiveLoginInfo(int& state);


//inline function
    QTcpSocket* getTcpSender()
    {
        return TcpSenderSocket;
    }
    QTcpSocket* getTcpReceiver()
    {
        return TcpReceiverSocket;
    }

    QUdpSocket* getUdpSender()
    {
        return UdpSenderSocket;
    }
    QUdpSocket* getUdpReceiver()
    {
        return UdpReceiverSocket;
    }

private slots:



private:
    QTcpSocket *TcpSenderSocket;
    QTcpSocket *TcpReceiverSocket;
    QUdpSocket* UdpSenderSocket;
    QUdpSocket* UdpReceiverSocket;
};



#endif // CLIENTSOCKET_H
