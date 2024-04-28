#include "ClientSocket.h"

////////////////////////////////////////////network////////////////////////////////////////
Network::Network(QObject *parent)
{
    qDebug() << "Create Client Success";
}

Network::~Network()
{
    delete TcpSenderSocket, TcpReceiverSocket, UdpSenderSocket, UdpReceiverSocket;
    qDebug() << "Destory Client";
}

int Network::createSocket(QObject* parent, QObject *receiver, int protocol)
{
    if( protocol == PROTOCOL_TCP)
    {
        //creat tcp socket
        TcpSenderSocket = new QTcpSocket(parent);
        TcpReceiverSocket = new QTcpSocket(receiver);
        qDebug() << "create TCP Socket successed";
    }
    else if(PROTOCOL_UDP)
    {
        //create udp socket
        UdpSenderSocket = new QUdpSocket();
        UdpReceiverSocket = new QUdpSocket();
        qDebug() << "create UDP Socket successed";
    }
    return OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////TCP////////////////////////////////////////////////////////////////////
int Network::sendByTcp(QString Username, QString Password)
{
    QString sendMessage;
    sendMessage.assign(Username+'\n'+Password);
    QByteArray datagram = sendMessage.toUtf8();
    if( TcpSenderSocket->write(datagram) == -1 )
    {
        qDebug() << "send error\n"<< "reason is"  <<   TcpSenderSocket->error();
        return ERROR;
    }
    if ( TcpSenderSocket->waitForBytesWritten())
    {
        qDebug() << "send successed";
    }
    else
    {
        qDebug() << "send error\n" << "reason is" << TcpSenderSocket->error();
        return ERROR;
    }
    return OK;
}
int Network::TcpConnect( QString ServerAddress, quint16 ServerPort)
{
    qDebug() << "Server IP Address is"<< ServerAddress;
    qDebug() << "Server port is"<<ServerPort;
    qDebug() << "waiting for connect to host";
    //Tcp connect
    TcpSenderSocket->connectToHost(ServerAddress, ServerPort);
    if(TcpSenderSocket->waitForConnected())
    {
        qDebug() << "TCP Connected!";
        qDebug() << "create send socket sussess";
        return OK;
    }
    else
    {
        qDebug() << "TCP Connect not found";
        qDebug() << TcpSenderSocket->error( );
        return ERROR;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////UDP///////////////////////////////////////////////////////////////////////////////////
int Network::sendByUdp(QString Username, QString Password, QHostAddress ServerAddress, quint16 ServerPort)
{
    QString sendMessage;
    sendMessage.assign(Username+'\n'+Password);
    qDebug() << "parper to send message:" << sendMessage;
    QByteArray datagram = sendMessage.toUtf8();
    qDebug() << "connect to " << ServerAddress.toString() << ":" << ServerPort;
    if(UdpSenderSocket->writeDatagram(datagram.data(), datagram.size(), ServerAddress, ServerPort) == -1)
    {
        UdpSenderSocket->error();
        return ERROR;
    }
    else
    {
        qDebug() << "UDP send have done";
        return OK;
    }
}

int Network::UdpBind(QHostAddress ServerAddress, quint16 ServerPort)
{
    qDebug() << "waiting for bind UDP socket";
    if (UdpSenderSocket->bind(ServerAddress, ServerPort, QUdpSocket::DefaultForPlatform))
    {
        qDebug() << "UDP Socket Bind Successed!";
        return OK;
    }
    else
    {
        qDebug() << "UDP Socket Bind Failed";
        qDebug() << "Reason is:" << UdpReceiverSocket->error();
        return ERROR;
    }
}

////////////////////////////////////////////////////////////////////////////////////////


void Network::ClientReceiveData()
{

}





int Network::receiveLoginInfo(int& state)
{
    /*
    client.receiveLoginInfo(state);
    if( state == LOGINSUSSESS )
    {
        QMessageBox::information(this, (QString)"info", (QString)"login sussess");
        QWidget *mainWidget  = new Widget();
        this->close();
        mainWidget->showMaximized();
    }
    else
    {
        QMessageBox::critical(this, (QString)"Error", (QString)"login fail");
    }
    */

    qDebug() << "receive LoginInfo";
    state = LOGINSUSSESS;
    return OK;
}


