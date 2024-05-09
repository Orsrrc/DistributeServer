#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <ctime>
#include <openssl/sha.h>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
//
// define log number
//
#define OK 0
#define ERROR -1
#define STABLISH 0
#define SERVER_PORT 9800
#define PROTOCOL_TCP 0
#define PROTOCOL_UDP 1
#define BUFFER_SIZE 128
////////////////////////////////GLOBAL////////////////////////////////////////////////////////////////////////////

int shardNum = 0;
int SourceNum = 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
    一个分片包括 第k总资源的分配量
    分片ID
    ID可查询
    分片长度  map <ID, length>
    分片地址  map <ID, shard address>
    创建分片 即动态申请一段地址空间
    map 用于存储ID 以及对应的长度 方便查询
*/

class shard
{
    public:
    shard(int id)
    :ID(id)
    {
        ;
    }
    ~shard();

    double getResAllocateInfo(int resourceType)
    {
        
        for(auto iterator = resouce_allocate_info.begin();iterator != resouce_allocate_info.end(); iterator++ )
        {
            if(iterator->first == resourceType)
            {
                return iterator->second;
            }
        }
        perror("error: no such resource");
        return ERROR;
    }

    int getShardLength()
    {
        return shard_length;
    }

    int setShardLength(int length = -1)
    {
        if(length == -1)
        {
            perror("error: length value is wrong");
            return ERROR;
        }
        shard_length = length;
        return OK;
    }

private:
    std::map<int, double> resouce_allocate_info; // map <resource ID : res (ID) allocate to shard i
    int ID;
    int shard_length; 
};

///////////////////////////////////GLOBAL FUNCTION///////////////////////////////////////////////////////////////

std::string get_current_time()
{
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string time = std::ctime(&now_time);
    return time;
}

std::string generateRandomString(int length = ((rand() + 100) % 10))
{
    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()_+{}[]|;:,.<>?";
    const int charsetLength = charset.length();
    std::string result;
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < length; ++i)
    {
        result += charset[rand() % charsetLength];
    }

    return result;
}

std::string generateRandomDigit(int length = ((rand() + 100) % 10))
{
    const std::string charset = "0123456789";
    const int charsetLength = charset.length();
    std::string result;
    srand(time(0)); // Seed the random number generator
    for (int i = 0; i < length; ++i)
    {
        result += charset[rand() % charsetLength];
    }
}

// how to compel :g++ -o main main.cpp -lssl -lcrypto
std::string SHA256(const std::string &input)
{
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input.c_str(), input.size());
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    return ss.str();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////










#endif // COMMON_H
