#ifndef __RANDOM__H_
#define __RANDOM__H_

#include <algorithm>
#include <cstdlib> // For rand()
#include <cmath>
#include "../../Common.hpp"


class random
{
    int allocate(int ShardNum);

};

#endif //__RANDOM__H_