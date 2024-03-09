#include "ProcessServer.h"

int ProcessServer::Algorithm::Drift_Plus_Penalty_Resouce_Allocation(const int &resourceIndex,
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
    double temp = 0;

    for (int i; i < shardNum; i++)
    {
        temp = ProcessServer::Algorithm::Resource_Allocation_Per_Timeslot(resourceIndex,
                                                                          shardIndex,
                                                                          virtualQueuesIndex,
                                                                          actualQueuesIndex,
                                                                          queuesSet,
                                                                          virtualQueues,
                                                                          actualQueues,
                                                                          timeslotSet,
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
    ProcessServer processServer;
    for (int i = 0; i < SourceNum; i++)
    {
        // p(i, k) = (V/(alpha*(Weight(k)^alpha)* (Q(i) + RTX*V )))^(1/（alpha-1) )
        elements = virtualQueues[virtualQueuesIndex] + penltyWeight;
        denominator = alpha * pow(processServer.the_weight_of_the_resource(resourceIndex), alpha) * (actualQueues[actualQueuesIndex] + penltyWeight * reward);
        long double temp = (elements / denominator) * 1.0;
        processServer.the_kth_resource_allocated_to_shard(processServer.the_kth_resource_name(resourceIndex),
                                                           processServer.the_address_of_the_ith_shard(shardIndex),
                                                           pow(temp, (1 / (alpha - 1))));

        // B(i) = B(i) + (Weight(k) * p(i, k))^alpha
        processServer.the_dequeued_transaction_of_queue(i, processServer.the_dequeued_transaction_of_queue(i) + pow((processServer.the_weight_of_the_resource(resourceIndex) * processServer.the_kth_resource_allocated_to_shard(processServer.the_kth_resource_name(resourceIndex),
                                                                                                                                                                         processServer.the_address_of_the_ith_shard(shardIndex))),
                                                                                        alpha));

        // P(k) = P(k) + p(i, k)
    }
    return OK;
}
