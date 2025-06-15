#include "Longest.h"

int longest::allocate(std::vector<int> Q, int ShardNum)
{
    int SourceNum = 2;
    std::vector<int> MaxNum = {3300, 3000}; // Maximum resource values
    std::vector<int> Weight = {5, 4};       // Weights for resources
    double alpha = 0.5;

    std::vector<double> B(ShardNum, 0.0);
    std::vector<double> P(SourceNum, 0.0);
    std::vector<std::vector<double>> p(ShardNum, std::vector<double>(SourceNum, 0.0));

    // Find the shard with the longest queue
    std::vector<std::pair<int, int>> shardQueuePairs;
    for (int i = 0; i < ShardNum; ++i)
    {
        shardQueuePairs.push_back({Q[i], i});
    }
    sort(shardQueuePairs.begin(), shardQueuePairs.end(), std::greater<std::pair<int, int>>());

    // Allocate resources to the shard with the longest queue
    int longestShardIndex = shardQueuePairs[0].second;
    for (int k = 0; k < SourceNum; ++k)
    {
        p[longestShardIndex][k] = MaxNum[k];
        B[longestShardIndex] += pow(Weight[k] * p[longestShardIndex][k], alpha);
        P[k] = MaxNum[k];
    }

    // Output the results
    std::cout << "Shard Allocations:\n";
    for (int i = 0; i < ShardNum; ++i)
    {
        std::cout << "Shard " << i + 1 << ": ";
        for (int k = 0; k < SourceNum; ++k)
        {
            std::cout << "Resource " << k + 1 << ": " << p[i][k] << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nResource Allocations:\n";
    for (int k = 0; k < SourceNum; ++k)
    {
        std::cout << "Resource " << k + 1 << ": " << P[k] << std::endl;
    }

    return OK;
}

int longest::get_longest_shard_id(std::map<int, int> shard_length)
{
    int ID = 0;
    int longest = 0;
    for (auto iterator = shard_length.begin(); iterator != shard_length.end(); iterator++)
    {
        if (iterator->second > longest)
        {
            ID = iterator->first;
        }
    }

    return ID;
}


/*
int main() {
    const int ShardNum = 4;
    int Q[ShardNum] = {10, 20, 15, 25}; // Example queue lengths

    vector<int> B, P;
    Longest(Q, ShardNum, B, P);

    return 0;
}

*/

int longest::res_longest(int Q[], int ShardNum, vector<int> &B, vector<int> &P)
{

    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000}; // MaxNum[0] for Power, MaxNum[1] for Bandwidth
    vector<int> Weight = {5, 4};       // Weight[0] for Power, Weight[1] for Bandwidth
    double alpha = 0.5;
    int RTX = 5;

    B = vector<int>(ShardNum, 0);
    P = vector<int>(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));

    vector<pair<int, int>> queueIndices; // Pair of (queue length, shard index)
    for (int i = 0; i < ShardNum; ++i)
    {
        queueIndices.push_back({Q[i], i});
    }
    sort(queueIndices.begin(), queueIndices.end(), greater<pair<int, int>>());

    for (int k = 0; k < SourceNum; ++k)
    {
        p[queueIndices[0].second][k] = MaxNum[k];
        B[queueIndices[0].second] += pow(Weight[k] * p[queueIndices[0].second][k], alpha);
        P[k] = MaxNum[k];
    }

    cout << "Resource allocation using longest queue first:\n";
    cout << "B: ";
    for (int b : B)
    {
        cout << b << " ";
    }
    cout << endl;

    cout << "P: ";
    for (int p_val : P)
    {
        cout << p_val << " ";
    }
    cout << endl;
}
