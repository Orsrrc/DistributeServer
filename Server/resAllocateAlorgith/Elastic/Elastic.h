#ifndef __ELASTIC__H_
#define __ELASTIC__H_

#include "../../Common.hpp"
#include <map>
#include <vector>
#include <string>


class elastic
{
    public:
    shard *the_address_of_the_ith_shard(const int &i)
    {
        std::map<int, shard *>::iterator iterator = shardAddress.find(i);
        return iterator->second;
    }

    double the_kth_resource_allocated_to_shard(const std::string &resourceName, shard *Shard)
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

    
};



#endif //__ELASTIC__H_

