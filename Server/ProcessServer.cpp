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
    for (auto time : timeslotSet)
    {
        temp = ProcessServer::Algorithm::Resource_Allocation_Per_Timeslot(resourceType,
                                                                          queuesSet,
                                                                          time, 
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


double the_weight_of_the_resource(double resourceType);

int ProcessServer::Algorithm::Resource_Allocation_Per_Timeslot(const double &resourceType,
                                                               const std::vector<double> &queuesSet,
                                                               const double &timeslot,
                                                               std::vector<double> virtualQueues,
                                                               std::vector<double> actualQueues,
                                                               const double &penltyWeight,
                                                               const double &reward,
                                                               const double &alpha,
                                                               std::vector<long double> reAllocate)
{
    double denominator = 0;
    double elements = 0;
    for (double index : queuesSet)
    {
        elements = virtualQueues[resourceType] + penltyWeight;
        denominator = alpha*pow(the_weight_of_the_resource(resourceType), alpha)*(actualQueues[index] + penltyWeight*reward);
        long double temp = (elements/denominator) * 1.0;
        reAllocate[index] = std::sqrt(temp);
    }
    return OK;
}


double the_data_amount_processed(double resourceWeight)