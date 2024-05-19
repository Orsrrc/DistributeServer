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

    int Performance_evaluation_while_varying_parameter_V();
    int Performance_comparison_with_baseline_algorithms();
    int Performance_evaluation_under_the_continued_burstyTX_injection_attack_against_all_network_shards();
    int Performance_evaluation_under_the_drastic_burstyTX_injection_attack_against_a_single_network_shard();

private:
};

#endif //__PROCESS__SERVER__H_