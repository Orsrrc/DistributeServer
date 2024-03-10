#ifndef COMMON_H
#define COMMON_H

#include <http.h>


class Client
{
public:
    Client();
    ~Client();

    int sendLoginInfo( );
    int receiveLoginInfo();
};










#endif // COMMON_H
