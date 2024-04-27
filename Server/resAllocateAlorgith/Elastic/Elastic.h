#ifndef __ELASTIC__H_
#define __ELASTIC__H_

#include "../../Common.hpp"
#include <map>
#include <vector>
#include <string>
#include <math.h>

class elastic
{

    int Drift_Plus_Penalty_Resouce_Allocation(std::vector<int> shardSet,
                                              std::map<int, std::string> resouceSet,
                                              double penltyWeight,
                                              double alpha,
                                              double reward);

    int Resource_Allocation_Per_Timeslot(int shardIndex,
                                         std::map<int, std::string> resouceSet,
                                         double penltyWeight,
                                         double alpha,
                                         double reward,
                                         double shardLength);
};

#endif //__ELASTIC__H_
