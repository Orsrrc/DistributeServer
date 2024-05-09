#ifndef __NETWORK__HPP_
#define __NETWORK__HPP_

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <stdio.h>
#include "Common.hpp"
#include <unistd.h>
#include <net/if.h>
#include <ifaddrs.h>

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
    char *getReceiveMessage()
    {
        return recvBuffer;
    }
    char *getSenderMessage()
    {
        return sendBuffer;
    }

    int createSocket(int protocol);
    int receiver(int protocol);
    int sender(int protocol);
    int broadcastIP(std::string port, std::string ServerID);
    std::string getLocalIpAddress();
    std::string getLocalID();

private:
    TcpSocket *TcpSenderSocket;
    TcpSocket *TcpReceiverSocket;
    UdpSocket *UdpSenderSocket;
    UdpSocket *UdpReceiverSocket;

    struct sockaddr_in client;

    int clientSocketfd = 0;
    char recvBuffer[BUFFER_SIZE];
    char resAddress[64];
    char sendBuffer[BUFFER_SIZE];
};

class IPAddress
{
};

///////////////////////////////////////////////////////////////////TCP ////////////////////////////////////////////////////////////////////////////////////////
TcpSocket::TcpSocket(const std::string IpAddress, const std::string Port)
{
    int opt = 1;
    Socketfd = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "creating TCP Socket...." << std::endl;
    if (Socketfd == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    else
    {
        std::cout << "create TCP socket successed! socketfd is: " << Socketfd << std::endl;
    }

    if (setsockopt(Socketfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
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
        std::cout << "create UDP socket failed....reason is";
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
        perror("bind");
        std::cout << "bind socket failed....";
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
    createSocket(PROTOCOL_UDP);
    std::cout << std::endl;
    sleep(1);
    createSocket(PROTOCOL_TCP);
}

inline Network::~Network()
{
    close(UdpSenderSocket->getSocketfd());
    close(TcpReceiverSocket->getSocketfd());
    close(UdpReceiverSocket->getSocketfd());
    delete TcpReceiverSocket, UdpReceiverSocket, UdpSenderSocket;
}

inline int Network::createSocket(int protocol)
{
    if (protocol == PROTOCOL_TCP)
    {
        TcpReceiverSocket = new TcpSocket();
    }
    else if (protocol == PROTOCOL_UDP)
    {
        // UdpSenderSocket = new UdpSocket();
        UdpReceiverSocket = new UdpSocket();
    }
    else
    {
        perror("error protocol type");
        exit(EXIT_FAILURE);
    }
    
    return OK;
}

inline int Network::receiver(int protocol)
{
    int length = 0;
    bool isflag = true;
    if (protocol == PROTOCOL_TCP)
    {
        
        struct sockaddr_in server;
        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = INADDR_ANY;
        server.sin_port = htons(SERVER_PORT);

        int addrlen = sizeof(server);
        int Socketfd = TcpReceiverSocket->getSocketfd();
        int client_socket = -1;
        int valread = 0;

        // 绑定套接字
        if (bind(Socketfd, (struct sockaddr *)&server, sizeof(server)) == -1)
        {
            perror("bind");
            close(Socketfd);
            exit(EXIT_FAILURE);
        }
        std::cout << "bind IP address successed!" << std::endl;

        std::cout << "listening:" << Socketfd << std::endl;
        if (listen(Socketfd, 128) == -1)
        {
            perror("listen");
            close(Socketfd);
            exit(EXIT_FAILURE);
        }

        if ((client_socket = accept(Socketfd, (struct sockaddr *)&server,
                                 (socklen_t *)&addrlen)) < 0)
        {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        std::cout << "receive from:" << inet_ntop(AF_INET, &client.sin_addr.s_addr, resAddress, sizeof(resAddress)) << " "
                      << "port:" << ntohs(client.sin_port) << std::endl;



        valread = read(client_socket, recvBuffer, BUFFER_SIZE);
        printf("%s\n", recvBuffer);


        //send(client_socket, hello, strlen(hello), 0);
        //printf("Hello message sent\n");
        return 0;

        /*
        while (isflag)
        {
            socklen_t length = sizeof(client);
            std::cout << "waiting for connect....." << std::endl;
            clientSocketfd = accept(TcpReceiverSocket->getSocketfd(), (struct sockaddr *)&client, &length);
            
            if (clientSocketfd == -1)
            {
                perror("accept");
                close(TcpReceiverSocket->getSocketfd());
                exit(EXIT_FAILURE);
            }
            length = read(clientSocketfd, recvBuffer, sizeof(recvBuffer) - 1);
            if (length == -1)
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
        */
    }
    else if (protocol == PROTOCOL_UDP)
    {
        while (isflag)
        {
            struct sockaddr_in client;
            socklen_t length = sizeof(client);
            std::cout << "waiting for connect....." << std::endl;
            ssize_t size = recvfrom(UdpReceiverSocket->getSocketfd(), // 通信套接字fd
                                    recvBuffer,                       // 缓冲区首地址
                                    sizeof(recvBuffer) - 1,           // 缓冲区大小 ssize_t == long
                                    0,                                // flag
                                    (struct sockaddr *)&client,       // 客户端对象
                                    &length);                         // 地址长度

            std::cout << "Receive from:" << inet_ntop(AF_INET, &client.sin_addr.s_addr, resAddress, sizeof(resAddress)) << " "
                      << "Port:" << ntohs(client.sin_port) << std::endl;
            std::cout << "message is :" << recvBuffer << std::endl;
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
    if (protocol == PROTOCOL_UDP)
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
    else if (protocol == PROTOCOL_TCP)
    {
        if (write(clientSocketfd, sendBuffer, sizeof(sendBuffer)) == -1)
        {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    return OK;
}

inline int Network::broadcastIP(std::string port, std::string ServerID)
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return ERROR;
    }

    struct sockaddr_in broadcast_addr;
    memset(&broadcast_addr, 0, sizeof(broadcast_addr));
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_port = htons(std::stoi(port));

    // broadcast address 255.255.255.255
    in_addr_t addr = INADDR_BROADCAST;

    broadcast_addr.sin_addr.s_addr = addr;

    const std::string message = "ServerID:" + ServerID + "\n" + "IPAddress" + getLocalIpAddress() + "\n";
    ssize_t send_len = sendto(sockfd, message.c_str(), strlen(message.c_str()), 0,
                              (struct sockaddr *)&broadcast_addr, sizeof(broadcast_addr));

    if (send_len < 0)
    {
        std::cerr << "Sendto failed" << std::endl;
        close(sockfd);
        return -1;
    }

    std::cout << "Broadcast message sent" << std::endl;
    close(sockfd);
    return 0;
}

inline std::string Network::getLocalIpAddress()
{
    std::string ipAddress = "Error Unknown IPAddress";
    struct ifaddrs *ifaddr, *ifa;
    if (getifaddrs(&ifaddr) == -1)
    {
        return ipAddress;
    }
    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if (ifa->ifa_addr == NULL)
        {
            continue;
        }
        if (ifa->ifa_addr->sa_family == AF_INET)
        {
            struct sockaddr_in *addr = (struct sockaddr_in *)ifa->ifa_addr;
            if (strcmp(ifa->ifa_name, "lo") != 0 && addr->sin_addr.s_addr != INADDR_LOOPBACK)
            {
                char ip[INET_ADDRSTRLEN];
                inet_ntop(AF_INET, &addr->sin_addr, ip, INET_ADDRSTRLEN);
                ipAddress = ip;
                break;
            }
        }
    }
    freeifaddrs(ifaddr);
    return ipAddress;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
#endif //__NETWORK__H_
