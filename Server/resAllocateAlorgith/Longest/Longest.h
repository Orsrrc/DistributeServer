#ifndef __LONGEST__H_
#define __LONGEST__H_

#include "../../Common.hpp"


class longest
{
    int get_longest_shard_id(std::map<int, int> shardSet);

    int allocate(std::map<int, std::string> resourceSet);

};



#endif //__LONGEST__H_ 