#include "ClientSocket.h"

////////////////////////////////////////////network////////////////////////////////////////
Network::Network(QObject *parent)
{
    qDebug() << "Create Client Success";
}

Network::~Network()
{
    delete TcpSenderSocket, TcpReceiverSocket, UdpSenderSocket, UdpReceiverSocket;
    qDebug() << "Destory Client Socket";
}

int Network::createSocket(QObject* parent , int protocol)
{
    if( protocol == PROTOCOL_TCP)
    {
        //creat tcp socket
        TcpSenderSocket = new QTcpSocket(parent);
        qDebug() << "create TCP Socket successed";
    }
    else if(PROTOCOL_UDP)
    {
        //create udp socket
        UdpSenderSocket = new QUdpSocket();
        qDebug() << "create UDP Socket successed";
    }
    return OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////TCP////////////////////////////////////////////////////////////////////
int Network::sendByTcp(QString Username, QString Password)
{

    if( TcpSenderSocket->isOpen() )
    {
        //package send message
        QString sendMessage;
        sendMessage.assign(Username+'\n'+Password);

        if( TcpSenderSocket->write(sendMessage.toUtf8()) == -1 )
        {
            qDebug() << "Send Error\n"<< "reason is"  <<   TcpSenderSocket->error();
            return ERROR;
        }
        else
        {
             qDebug() << "Send Successed!";
        }
        /*
        else if ( TcpSenderSocket->waitForBytesWritten())
        {
            qDebug() << "Send Successed!";
        }

        else
        {
            qDebug() << "Send Error!\n" << "reason is" << TcpSenderSocket->error();
            return ERROR;
        }
    */
    }

    //socket close
    TcpSenderSocket->disconnectFromHost();
    TcpSenderSocket->close();

    return OK;
}
int Network::TcpConnect( QString ServerAddress, quint16 ServerPort)
{
    qDebug() << "Server IP Address is"<< ServerAddress;
    qDebug() << "Server port is"<<ServerPort;


    //Tcp connect
    TcpSenderSocket->connectToHost( ServerAddress, ServerPort);


    qDebug() << "Waiting for connect to host......";
    if(TcpSenderSocket->waitForConnected())
    {
        qDebug() << "TCP Connected!";
        qDebug() << "Create sender socket sussess";
        return OK;
    }
    else
    {
       qDebug() << "Failed to connect to server:" <<TcpSenderSocket->errorString();
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


