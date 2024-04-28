#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

void Longest(int Q[], int ShardNum, vector<int>& B, vector<int>& P) {
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000}; // MaxNum[0] for Power, MaxNum[1] for Bandwidth
    vector<int> Weight = {5, 4}; // Weight[0] for Power, Weight[1] for Bandwidth
    double alpha = 0.5;
    int RTX = 5;

    B = vector<int>(ShardNum, 0);
    P = vector<int>(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));

    vector<pair<int, int>> queueIndices; // Pair of (queue length, shard index)
    for (int i = 0; i < ShardNum; ++i) {
        queueIndices.push_back({Q[i], i});
    }
    sort(queueIndices.begin(), queueIndices.end(), greater<pair<int, int>>());

    for (int k = 0; k < SourceNum; ++k) {
        p[queueIndices[0].second][k] = MaxNum[k];
        B[queueIndices[0].second] += pow(Weight[k] * p[queueIndices[0].second][k], alpha);
        P[k] = MaxNum[k];
    }

    cout << "Resource allocation using longest queue first:\n";
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

int main() {
    const int ShardNum = 4;
    int Q[ShardNum] = {10, 20, 15, 25}; // Example queue lengths

    vector<int> B, P;
    Longest(Q, ShardNum, B, P);

    return 0;
}
