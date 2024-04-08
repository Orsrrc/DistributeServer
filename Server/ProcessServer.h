#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <map>

class ProcessServer
{
public:
    class elasticAlgorithm
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


    private:
};