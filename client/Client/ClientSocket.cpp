#include "ClientSocket.h"


Client::Client()
{
    qDebug() << "create Client";
}

Client::~Client()
{
    qDebug() << "destory Client";
}

int Client::sendLoginInfo()
{
    qDebug() << "SendLoginInfor";
    return OK;
}

int Client::receiveLoginInfo(int& state)
{
    qDebug() << "receive LoginInfo";
    state = LOGINSUSSESS;
    return OK;
}


