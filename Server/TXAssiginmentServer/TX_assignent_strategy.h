#ifndef TX_ASSIGNENT__STRATEGY_H_
#define TX_ASSIGNENT__STRATEGY_H_
/*
	交易分配服务器：
	1、根据客户端发送的交易数据量产生对应的交易量
	2、通过交易分配算法将交易分配到不同的网络分片中
	


*/

#include  <iostream>
#include <vector>


class TX_strategy
{
	int avarageAssigment(std::vector<std::string> hash);

};




#endif //TX_ASSIGNENT__STRATEGY_H_