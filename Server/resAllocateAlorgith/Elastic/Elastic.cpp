#include "Elastic.h"


int elastic::Drift_Plus_Penalty_Resouce_Allocation(
    std::vector<int> shardSet,
    std::map<int, std::string> resouceSet,
    double penltyWeight,
    double alpha,
    double reward)
{
    double temp = 0;
    for (int i = 0; shardSet[i] != NULL; i++)
    {
        temp = elastic::Resource_Allocation_Per_Timeslot(shardSet[i], resouceSet, penltyWeight, alpha, reward, get_the_length_of_the_actual_shard(shardSet[i]));
        if (!temp)
        {
            return ERROR;
        }
    }

    return OK;
}

int elastic::Resource_Allocation_Per_Timeslot(
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



int res_elastic(int Q[], int Z[], int ShardNum, int V) {
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000}; // MaxNum[0] for Power, MaxNum[1] for Bandwidth
    vector<int> Weight = {5, 4}; // Weight[0] for Power, Weight[1] for Bandwidth
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 1;
    int SlotsInterval = 1;

    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));

    for (int i = 0; i < ShardNum; ++i) {
        for (int k = 0; k < SourceNum; ++k) {
            p[i][k] = pow((V + Z[k]) / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    cout << "Resource allocation when resources are abundant:\n";
    cout << "B: ";
    for (int b : B) {
        cout << b << " ";
    }
    cout << endl;

    cout << "P: ";
    for (int p_val : P) {
        cout << p_val << " ";
    }
    cout << endl;
}
