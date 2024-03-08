#include "ProcessServer.h"
#include "../Common.h"

int ProcessServer::Algorithm::Drift_Plus_Penalty_Resouce_Allocation(const double &resourceType,
                                                                    const std::vector<double> &queuesSet,
                                                                    std::vector<double> virtualQueues,
                                                                    std::vector<double> actualQueues,
                                                                    const std::vector<double> &timeslotSet,
                                                                    const double &penltyWeight,
                                                                    const double &reward,
                                                                    const double &alpha,
                                                                    std::vector<long double> reAllocate)
{
    double temp = 0;

    for (int i; i < shardNum; i++)
    {
        temp = ProcessServer::Algorithm::Resource_Allocation_Per_Timeslot(resourceType,
                                                                          queuesSet,
                                                                          timeslotSet,
                                                                          virtualQueues,
                                                                          actualQueues,
                                                                          penltyWeight,
                                                                          reward,
                                                                          alpha,
                                                                          reAllocate);

        if (!temp)
        {
            return ERROR;
        }
    }

    return OK;
}

int ProcessServer::Algorithm::Resource_Allocation_Per_Timeslot(const int &resourceIndex,
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
                                                               std::vector<long double> reAllocate)
{
    double denominator = 0;
    double elements = 0;
    double dequeuedTransaction = 0;
    int index = 0;

    for (int i = 0; i < SourceNum; i++)
    {
        // p(i, k) = (V/(alpha*(Weight(k)^alpha)* (Q(i) + RTX*V )))^(1/（alpha-1) )
        elements = virtualQueues[virtualQueuesIndex] + penltyWeight;
        denominator = alpha * pow(the_weight_of_the_resource(resourceIndex), alpha) * (actualQueues[actualQueuesIndex] + penltyWeight * reward);
        long double temp = (elements / denominator) * 1.0;
        the_kth_resource_allocated_to_shard(the_kth_resource_name(resourceIndex),
                                            the_address_of_the_ith_shard(shardIndex),
                                            pow(temp, (1 / (alpha - 1))));


        //B(i) = B(i) + (Weight(k) * p(i, k))^alpha
        the_dequeued_transaction_of_queue(i,  the_dequeued_transaction_of_queue(i) + pow((the_weight_of_the_resource(resourceIndex) * the_kth_resource_allocated_to_shard(the_kth_resource_name(resourceIndex),
                                                                                                                                                          the_address_of_the_ith_shard(shardIndex))),
                                                                         alpha)); 

        //P(k) = P(k) + p(i, k)
    }
    return OK;
}

shard *the_address_of_the_ith_shard(int i)
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