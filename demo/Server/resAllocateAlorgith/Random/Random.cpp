#include "Random.h"

int random::allocate(int ShardNum)
{
    int SourceNum = 2;
    std::vector<int> MaxNum = {3300, 3000};
    std::vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 24;
    int BlockInterval = 1;
    int SlotsInterval = 1;

    std::vector<double> B(ShardNum, 0.0);
    std::vector<double> P(SourceNum, 0.0);
    std::vector<std::vector<double>> p(ShardNum, std::vector<double>(SourceNum, 0.0));

    MaxNum[0] = rand() % 1501 + 1000; // Random value between 1000 and 2500
    MaxNum[1] = rand() % 1001 + 1000; // Random value between 1000 and 2000

    double sumA = 0.0;
    std::vector<double> A(ShardNum);
    for (int i = 0; i < ShardNum; ++i)
    {
        A[i] = rand() / (RAND_MAX + 1.0);
        sumA += A[i];
    }
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = MaxNum[k] * (A[i] / sumA);
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
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
