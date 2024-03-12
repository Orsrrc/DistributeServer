#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H

#include <http.h>
#include <QDebug>
#include <QString>


#include "common.h"


class Client
{
public:
    Client();
    ~Client();
    int sendLoginInfo( );
    int receiveLoginInfo(int& state);
};



#endif // CLIENTSOCKET_H
