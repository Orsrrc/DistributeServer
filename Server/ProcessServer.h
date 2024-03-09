#ifndef PROCESS__SERVER__H
#define PROCESS__SERVER__H

#include <iostream>
#include <vector>
#include <cmath>
#include "../Common.h"

class ProcessServer
{
public:
    shard *the_address_of_the_ith_shard(int i)
    {
        std::map<int, shard *>::iterator iterator = shardAddress.find(i);
        return iterator->second;
    }

    double ProcessServer::the_kth_resource_allocated_to_shard(const std::string &resourceName, shard *Shard)
    {
        std::map<std::string, double>::iterator iterator = Shard->resouceAllocateInfo.find(resourceName);
        return iterator->second;
    }

    int the_kth_resource_allocated_to_shard(const std::string &resourceName, shard *Shard, const long double &assiginNum)
    {
        std::map<std::string, double>::iterator iterator = Shard->resouceAllocateInfo.find(resourceName);
        iterator->second = assiginNum;
        return OK;
    }

    std::string the_kth_resource_name(int k)
    {
        std::map<int, std::string>::iterator iterator = resourceNameList.find(k);
        return iterator->second;
    }

    double the_data_amount_processed(double resourceWeight)
    {
        return OK;
    }

    int the_dequeueued_transactions_of_queue(int index)
    {
        return OK;
    }

    double the_weight_of_the_resource(const int &resourceType)
    {
        std::map<int, double>::iterator iterator = resourceWeightList.find(resourceType);
        return iterator->second;
    }

    double the_dequeued_transaction_of_queue(const int &queueIndex)
    {
        std::map<int, long double>::iterator iterator = dequeuedQueues.find(queueIndex);
        return iterator->second;
    }

    int the_dequeued_transaction_of_queue(const int &queueIndex, const long double &assiginNum)
    {
        std::map<int, long double>::iterator iterator = dequeuedQueues.find(queueIndex);
        iterator->second = assiginNum;
        return OK;
    }

    double the_kth_resource_allocated_to_shard(const std::string &resourceName, shard *Shard);

    class Algorithm
    {
        int Drift_Plus_Penalty_Resouce_Allocation(const int &resourceIndex,
                                                  const int &shardIndex,
                                                  const int &virtualQueuesIndex,
                                                  const int &actualQueuesIndex,
                                                  const std::vector<double> &queuesSet,
                                                  std::vector<double> virtualQueues,
                                                  std::vector<double> actualQueues,
                                                  const std::vector<double> &timeslotSet,
                                                  const double &penltyWeight,
                                                  const double &reward,
                                                  const double &alpha,
                                                  std::vector<long double> reAllocate);

        int Resource_Allocation_Per_Timeslot(const int &resourceIndex,
                                             const int &shardIndex,
                                             const int &virtualQueuesIndex,
                                             const int &actualQueuesIndex,
                                             const std::vector<double> &queuesSet,
                                             std::vector<double> virtualQueues,
                                             std::vector<double> actualQueues,
                                             const std::vector<double> &timeslotSet,
                                             const double &penltyWeight,
                                             const double &reward,
                                             const double &alpha,
                                             std::vector<long double> reAllocate);
    };

private:
};

#endif //__PROCESS__SERVER__H_