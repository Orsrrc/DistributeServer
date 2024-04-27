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