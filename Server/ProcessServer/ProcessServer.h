/*
数据处理服务器：
1、根据网络所传送的字符串来决定资源分配算法
2、确定对应的资源分配算法后 运行对应的算法 将数据发送给数据库以及客户端

*/

#ifndef PROCESS__SERVER__H
#define PROCESS__SERVER__H


#include <iostream>
#include <cmath>
#include <random>
#include "../Common.hpp"

class ProcessServer
{
    public:
        ProcessServer();
        ~ProcessServer();

    int simulation_shard_num();

    std::tuple<std::vector<double>, std::vector<double>> stop(std::vector<double> Q, int ShardNum);
private:
};

#endif //__PROCESS__SERVER__H_