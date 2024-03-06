#pragma once

#include <iostream>
#include <vector>
#include <cmath>
class ProcessServer
{
public:
    class Algorithm
    {
        int Drift_Plus_Penalty_Resouce_Allocation(const double &resourceType,
                                                  const std::vector<double> &queuesSet,
                                                  std::vector<double> virtualQueues,
                                                  std::vector<double> actualQueues,
                                                  const std::vector<double> &timeslotSet,
                                                  const double &penltyWeight,
                                                  const double &reward,
                                                  const double &alpha,
                                                  std::vector<long double> reAllocate);

        int Resource_Allocation_Per_Timeslot(const double &resourceType,
                                             const std::vector<double> &queuesSet,
                                             const double &timeslot,
                                             std::vector<double> virtualQueues,
                                             std::vector<double> actualQueues,
                                             const double &penltyWeight,
                                             const double &reward,
                                             const double &alpha,
                                             std::vector<long double> reAllocate);
    };

private:
};