#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void Elastic(int Q[], int Z[], int ShardNum, int V) {
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

int main() {
    const int ShardNum = 4;
    int Q[ShardNum] = {10, 20, 15, 25}; // Example queue lengths
    int Z[2] = {100, 200}; // Example resource types
    int V = 30; // Example transaction arrival rate

    Elastic(Q, Z, ShardNum, V);

    return 0;
}
