#ifndef __NETWORK__H_
#define __NETWORK__H_

// UDP protocol server
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "Common.hpp"

class TcpSocket
{
public:
    TcpSocket(const std::string IpAddress = " ", const std::string port = " ");
    ~TcpSocket();
    int getSocketfd()
    {
        return Socketfd;
    }

private:
    int Socketfd = -1;
};

class UdpSocket
{
public:
    UdpSocket(const std::string IpAddress = " ", const std::string port = " ");
    ~UdpSocket();
    int getSocketfd()
    {
        return Socketfd;
    }

private:
    int Socketfd = -1;
};

class Network
{
public:
    Network(const std::string IpAddress = " ", const std::string port = " ");
    ~Network();

    TcpSocket *getTcpReceiverSocket()
    {
        return TcpReceiverSocket;
    }
    UdpSocket *getUdpSenderSocket()
    {
        return UdpSenderSocket;
    }
    UdpSocket *getUdpReceiverSocket()
    {
        return UdpReceiverSocket;
    }
    int initSocket(int protocol);
    int receiver(int protocol);
    int sender(int protocol);
private:
    TcpSocket *TcpReceiverSocket;
    UdpSocket *UdpSenderSocket;
    UdpSocket *UdpReceiverSocket;

    struct sockaddr_in client;
    int clientSocketfd = 0;
    
    char recvBuffer[128];
    char resAddress[64];
    char sendBuffer[128];
};

/// ////////////////////////////////////////////////////////////////TCP ////////////////////////////////////////////////////////////////////////////////////////
TcpSocket::TcpSocket(const std::string IpAddress, const std::string Port)
{
    Socketfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "creating TCP Socket...." << std::endl;
    if (Socketfd == -1)
    {
        std::cout << "creat socket failed....reason is";
        perror("socket");
        std::cout << std::endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "create  socket successed! socketfd is: " << Socketfd << std::endl;
    }
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVER_PORT);
    // 绑定套接字
    if (bind(Socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        std::cout << "bind socket failed....reason is";
        perror("bind");
        std::cout << std::endl;
        close(Socketfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "bind IP address successed!" << std::endl;
}

TcpSocket::~TcpSocket()
{
    close(Socketfd);
    std::cout << "socket closed!" << std::endl;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////UDP//////////////////////////////////////////////////////////////////////////////////////////////////
UdpSocket::UdpSocket(const std::string IpAddress, const std::string Port)
{
    Socketfd = socket(AF_INET, SOCK_DGRAM, 0); // fd == file descriptor
    // create UDP Socket
    std::cout << "creating UDP Socket...." << std::endl;
    if (Socketfd == -1)
    {
        std::cout << "create socket failed....reason is";
        perror("socket");
        std::cout << std::endl;
        close(Socketfd);
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "create  socket successed! socketfd is" << Socketfd << std::endl;
    }
    struct sockaddr_in server;
    bzero(&server, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(SERVER_PORT);
    // 绑定套接字
    if (bind(Socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
    {
        std::cout << "bind socket failed....reason is";
        perror("bind");
        std::cout << std::endl;
        close(Socketfd);
        exit(EXIT_FAILURE);
    }
    std::cout << "bind IP address successed!" << std::endl;
}

UdpSocket::~UdpSocket()
{
    close(Socketfd);
    std::cout << "socket closed" << std::endl;
}
////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////network/////////////////////////////////////////////////////////

inline Network::Network(const std::string IpAddress, const std::string port)
{
    std::cout << "init Network" << std::endl;
}

inline Network::~Network()
{
    close(UdpSenderSocket->getSocketfd());
    close(TcpReceiverSocket->getSocketfd());
    close(UdpReceiverSocket->getSocketfd());
    delete TcpReceiverSocket, UdpReceiverSocket,UdpSenderSocket;
}

inline int Network::initSocket(int protocol)
{
    if (protocol == PROTOCOL_TCP)
    {
        TcpReceiverSocket = new TcpSocket();
    }
    else if (protocol == PROTOCOL_UDP)
    {
        UdpSenderSocket = new UdpSocket();
        UdpReceiverSocket = new UdpSocket();
    }
    else
    {
        perror("error protocol type");
        exit(EXIT_FAILURE);
    }
    std::cout << "init socket successed" << std::endl;
    return OK;
}

inline int Network::receiver(int protocol)
{
    int length = 0;
    bool isflag = true;
    if (protocol == PROTOCOL_TCP)
    {
        if( listen(TcpReceiverSocket->getSocketfd(), 128) == -1)
        {
            perror("listen");
            close(TcpReceiverSocket->getSocketfd());
            exit(EXIT_FAILURE);
        }
        while (isflag)
        {
            socklen_t length = sizeof(client);
            std::cout << "waiting for connect....." << std::endl;
            clientSocketfd = accept(TcpReceiverSocket->getSocketfd(), (struct sockaddr *)&client, &length);
            std::cout << "receive from:" << inet_ntop(AF_INET, &client.sin_addr.s_addr, resAddress, sizeof(resAddress)) << " " << "port:" << ntohs(client.sin_port) << std::endl;
            if(clientSocketfd == -1)
            {
                perror("accept");
                close(TcpReceiverSocket->getSocketfd());
                exit(EXIT_FAILURE);
            }
            length = read(clientSocketfd, recvBuffer, sizeof(recvBuffer) - 1);
            if( length == -1)
            {
                perror("read");
                close(UdpReceiverSocket->getSocketfd());
                close(clientSocketfd);
                exit(EXIT_FAILURE);
            }
            else if (length == 0)
            {
                std::cout << "receive message have done" << std::endl;
                isflag = false;
            }
            std::cout << recvBuffer << std::endl;
        }
    }
    else if (protocol == PROTOCOL_UDP)
    {
        while (isflag)
        {
            struct sockaddr_in client;
            socklen_t length = sizeof(client);
            std::cout << "waiting for connect....." << std::endl;
            ssize_t size = recvfrom(UdpReceiverSocket->getSocketfd(),                   // 通信套接字fd
                                recvBuffer,                     // 缓冲区首地址
                                sizeof(recvBuffer) - 1,         // 缓冲区大小 ssize_t == long
                                0,                          // flag
                                (struct sockaddr *)&client, // 客户端对象
                                &length);                   // 地址长度
            std::cout << "Receive from:" << inet_ntop(AF_INET, &client.sin_addr.s_addr, resAddress, sizeof(resAddress)) <<" "<< "Port:" << ntohs(client.sin_port) << std::endl;
            std::cout << "message is :"<< recvBuffer << std::endl;
            if (length < 0)
            {
                perror("recvfrom");
                close(UdpReceiverSocket->getSocketfd());
                exit(EXIT_FAILURE);
            }
            else if (length == 0)
            {
                isflag = false;
                std::cout << "receive have done" << std::endl;
            }
        }
    }
    else
    {
        perror("error protocol type");
        exit(EXIT_FAILURE);
    }
    return OK;
}

inline int Network::sender(int protocol)
{
    strcpy(sendBuffer, "OK");
    if(protocol == PROTOCOL_UDP)
    {
         if (sendto(UdpSenderSocket->getSocketfd(), sendBuffer, sizeof(sendBuffer) - 1, 0, (struct sockaddr *)&client, sizeof(client)) == -1)
        {
            perror("sendto");
        }
        else
        {
            std::cout << "send messages have done" << std::endl;
        }
    }
    else if(protocol == PROTOCOL_TCP)
    {
       if(  write(clientSocketfd, sendBuffer, sizeof(sendBuffer)) == -1)
       {
        perror("write");
        exit(EXIT_FAILURE);
       } 
    }
    return OK;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //__NETWORK__H_
