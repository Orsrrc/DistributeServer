#ifndef __DUALASCENT__H_
#define __DUALASCENT__H_

#include <vector>
#include <map>
#include <string>
#include <math.h>
#include <cmath>
#include <iostream>
#include "../../Common.hpp"

class dualascent
{

public:
    dualascent();
    ~dualascent();

    int getGamma(int resType);
    int setGamma(int resType, double value);
    int getResWeight(int resType);
    int getLamba(int shardID);
    int setLamba(int shardID, double value);

    int getResMax(int resType);

    int getShardLength(int shardID);
    double getShardTX(int shardID);
    int setShardTX(int shardID, double value);

    int getResUsage(int resType);
    int setResUseage(int resType, int value);

    int setResAllocate(int shardID, int resType, double value);

    int dualdecomposition_allocate(double maxIteration,
                                   std::vector<int> shardSet,
                                   std::map<int, std::string> resourceSet,
                                   double penltyWeight,
                                   double alpha,
                                   double reward,
                                   double shardLength);
    double max(int x, int y);
    double resCount(int begin, int end);

    int dualdecomposition_allocate();
};

#endif //__DUALASCENT__H_