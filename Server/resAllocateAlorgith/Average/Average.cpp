#include <iostream>
#include <vector>
#include <cmath>

void Average(int ShardNum) {
    int SourceNum = 2;
    std::vector<int> MaxNum = {3300, 3000}; // Maximum resource values
    std::vector<int> Weight = {5, 4}; // Weights for resources
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 1;
    int SlotsInterval = 1;

    // Vector to store shard allocations and resource allocations
    std::vector<double> B(ShardNum, 0.0);
    std::vector<double> P(SourceNum, 0.0);
    std::vector<std::vector<double>> p(ShardNum, std::vector<double>(SourceNum, 0.0));

    // Average Resource Allocation
    for (int i = 0; i < ShardNum; ++i) {
        for (int k = 0; k < SourceNum; ++k) {
            p[i][k] = MaxNum[k] / static_cast<double>(ShardNum);
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Output the results
    std::cout << "Shard Allocations:\n";
    for (int i = 0; i < ShardNum; ++i) {
        std::cout << "Shard " << i + 1 << ": ";
        for (int k = 0; k < SourceNum; ++k) {
            std::cout << "Resource " << k + 1 << ": " << p[i][k] << ", ";
        }
        std::cout << std::endl;
    }

    std::cout << "\nResource Allocations:\n";
    for (int k = 0; k < SourceNum; ++k) {
        std::cout << "Resource " << k + 1 << ": " << P[k] << std::endl;
    }
}

int main() {
    int numShards = 4;
    Average(numShards);
    return 0;
}
