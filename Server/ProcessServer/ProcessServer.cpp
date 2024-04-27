#include "ProcessServer.h"
#include "../Common.hpp"

int ProcessServer::elasticAlgorithm::Drift_Plus_Penalty_Resouce_Allocation(
    std::vector<int> shardSet,
    std::map<int, std::string> resouceSet,
    double penltyWeight,
    double alpha,
    double reward)
{
    double temp = 0;
    for (int i = 0; shardSet[i] != NULL; i++)
    {
        temp = ProcessServer::elasticAlgorithm::Resource_Allocation_Per_Timeslot(shardSet[i], resouceSet, penltyWeight, alpha, reward, get_the_length_of_the_actual_shard(shardSet[i]));
        if (!temp)
        {
            return ERROR;
        }
    }

    return OK;
}

int ProcessServer::elasticAlgorithm::Resource_Allocation_Per_Timeslot(
    int shardIndex,
    std::map<int, std::string> resouceSet,
    double penltyWeight,
    double alpha,
    double reward,
    double shardLength)
{
    double denominator = 0;
    double elements = 0;
    for (auto iterator = resouceSet.begin(); iterator != resouceSet.end(); iterator++)
    {
        elements = get_increment(iterator->first) + penltyWeight;
        denominator = alpha * pow(get_the_weight_of_the_resource(iterator->first), alpha) * (shardLength + penltyWeight * reward);
        long double temp = (elements / denominator) * 1.0;
        alter_the_kth_resource_allocated_to_shard(iterator->first, shardIndex, pow(temp, (1 / (alpha - 1))));
        alter_the_shard_i_dequeued_transaction(shardIndex,
                                               (get_the_shard_ith_dequeue_transaction(shardIndex) + pow((get_the_weight_of_the_resource(iterator->first) * get_the_kth_resource_allocated_to_shard(shardIndex, iterator->first)), alpha)));
    }
    return OK;
}

int ProcessServer::dualdecomposition::dualdecomposition_allocate(double maxIteration, std::vector<int> shardSet, std::map<int, std::string> resourceSet, double penltyWeight, double alpha, double reward, double shardLength)
{

    double allocate = 0;
    for (int j = 0; j < maxIteration; j++)
    {
        for (int i = 0; shardSet[i] != NULL; i++)
        {
            for (auto iterator = resourceSet.begin(); iterator != resourceSet.end(); iterator++)
            {
                allocate = ((penltyWeight - get_kth_resource_gamma_value(iterator->first)) 
                            / ( alpha * pow((get_the_weight_of_the_resource(iterator->first)), alpha) * ( get_the_length_of_the_actual_shard(shardSet[i])))
                            + pow( reward * penltyWeight + get_ith_shard_lamba_value(shardSet[i]) , (1/(alpha -1)) )
                            );
            }
        }
    }

    return 0;
}
