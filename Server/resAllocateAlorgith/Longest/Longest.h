#ifndef __LONGEST__H_
#define __LONGEST__H_

#include "../../Common.hpp"
#include <algorithm>
#include <cmath>
class longest
{
    int get_longest_shard_id(std::map<int, int> shardSet);

    int allocate(std::vector<int> Q, int ShardNum);

};



#endif //__LONGEST__H_ 