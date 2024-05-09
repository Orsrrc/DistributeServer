#include "ProcessServer.h"
#include "resAllocateAlorgith.h"
#include "../Common.hpp"

using namespace std;


int ProcessServer::simulation_shard_num()
{
    int ShardNum = 5;
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000};
    int T = 1000;
    vector<int> TimeSlot(T, 0);
    vector<vector<double>> Q(T, vector<double>(ShardNum, 0));
    vector<vector<double>> Z(T, vector<double>(SourceNum, 0));
    vector<vector<double>> Q100(T, vector<double>(ShardNum, 0));
    vector<vector<double>> Z100(T, vector<double>(SourceNum, 0));
    vector<vector<double>> Q150(T, vector<double>(ShardNum, 0));
    vector<vector<double>> Z150(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QE(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZE(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QV(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZV(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QST(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZST(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QL(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZL(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QAve(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZAve(T, vector<double>(SourceNum, 0));
    vector<vector<double>> QRand(T, vector<double>(ShardNum, 0));
    vector<vector<double>> ZRand(T, vector<double>(SourceNum, 0));

    vector<vector<double>> A(T, vector<double>(ShardNum, 0));
    vector<vector<double>> P(T, vector<double>(SourceNum, 0));
    vector<vector<double>> PE(T, vector<double>(SourceNum, 0));
    vector<vector<double>> BE(T, vector<double>(ShardNum, 0));
    vector<vector<double>> BSTop(T, vector<double>(ShardNum, 0));
    vector<vector<double>> PSTop(T, vector<double>(SourceNum, 0));
    vector<vector<double>> BLongest(T, vector<double>(ShardNum, 0));
    vector<vector<double>> PLongest(T, vector<double>(SourceNum, 0));
    vector<vector<double>> BAve(T, vector<double>(ShardNum, 0));
    vector<vector<double>> PAve(T, vector<double>(SourceNum, 0));
    vector<vector<double>> BRand(T, vector<double>(ShardNum, 0));
    vector<vector<double>> PRand(T, vector<double>(SourceNum, 0));
    vector<double> data1(T, 0);
    vector<double> data2(T, 0);
    vector<double> data3(T, 0);
    vector<double> DEL(T, 0);
    vector<double> DEP(T, 0);
    vector<double> DEB(T, 0);
    vector<double> DSTOPL(T, 0);
    vector<double> DSTOPP(T, 0);
    vector<double> DSTOPB(T, 0);
    vector<double> DLongL(T, 0);
    vector<double> DLongP(T, 0);
    vector<double> DLongB(T, 0);
    vector<double> DAveL(T, 0);
    vector<double> DAveP(T, 0);
    vector<double> DAveB(T, 0);
    vector<double> DRandL(T, 0);
    vector<double> DRandP(T, 0);
    vector<double> DRandB(T, 0);
    vector<double> ThroughputP(T, 0);
    vector<double> ThroughputE(T, 0);
    vector<double> ThroughputTOP(T, 0);
    vector<double> ThroughputLong(T, 0);
    vector<double> ThroughputAve(T, 0);
    vector<double> ThroughputRand(T, 0);
    vector<double> AA(T, 0);
    int V = 150;

    // Initialize random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(10, 30);

    // Generate random numbers for A
    for (int t = 0; t < T; ++t) {
        for (int i = 0; i < ShardNum; ++i) {
            A[t][i] = distribution(gen);
        }
    }

    for (int t = 0; t < T; ++t) {
        TimeSlot[t] = t;
        cout << t << endl;
        alorgith alorgith;
        // Call the functions implemented in C++
        BE[t] = alorgith.Elastic( Q[t], Z[t], 30, ShardNum);
        B[t] = alorgith.resallocation_lagrange(Q[t], 30, ShardNum);
        BSTop[t] = stop(QST[t], ShardNum);
        BLongest[t] = alorgith.Longest(QL[t], ShardNum);
        BAve[t] = alorgith.Average(ShardNum);
        BRand[t] = alorgith.Random(ShardNum);

        // Update Q and Z based on the results of the functions
        for (int i = 0; i < ShardNum; ++i) {
            Q[t+1][i] = max(Q[t][i] - B[t][i] + A[t][i], 0.0);
            QE[t+1][i] = max(QE[t][i] - BE[t][i] + A[t][i], 0.0);
            QST[t+1][i] = max(QST[t][i] - BSTop[t][i] + A[t][i], 0.0);
            QL[t+1][i] = max(QL[t][i] - BLongest[t][i] + A[t][i], 0.0);
            QAve[t+1][i] = max(QAve[t][i] - BAve[t][i] + A[t][i], 0.0);
            QRand[t+1][i] = max(QRand[t][i] - BRand[t][i] + A[t][i], 0.0);
        }

        // Update other variables
        data1[t] = accumulate(Q[t].begin(), Q[t].end(), 0.0);
        DEL[t] = accumulate(QE[t].begin(), QE[t].end(), 0.0);
        DSTOPL[t] = accumulate(QST[t].begin(), QST[t].end(), 0.0);
        DLongL[t] = accumulate(QL[t].begin(), QL[t].end(), 0.0);
        DAveL[t] = accumulate(QAve[t].begin(), QAve[t].end(), 0.0);
        DRandL[t] = accumulate(QRand[t].begin(), QRand[t].end(), 0.0);

        // Compute Throughput
        ThroughputP[t] = abs(accumulate(Q[t+1].begin(), Q[t+1].end(), 0.0) - accumulate(Q[t].begin(), Q[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));
        ThroughputE[t] = abs(accumulate(QE[t+1].begin(), QE[t+1].end(), 0.0) - accumulate(QE[t].begin(), QE[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));
        ThroughputTOP[t] = abs(accumulate(QST[t+1].begin(), QST[t+1].end(), 0.0) - accumulate(QST[t].begin(), QST[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));
        ThroughputLong[t] = abs(accumulate(QL[t+1].begin(), QL[t+1].end(), 0.0) - accumulate(QL[t].begin(), QL[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));
        ThroughputAve[t] = abs(accumulate(QAve[t+1].begin(), QAve[t+1].end(), 0.0) - accumulate(QAve[t].begin(), QAve[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));
        ThroughputRand[t] = abs(accumulate(QRand[t+1].begin(), QRand[t+1].end(), 0.0) - accumulate(QRand[t].begin(), QRand[t].end(), 0.0) - accumulate(A[t].begin(), A[t].end(), 0.0));

        AA[t] = accumulate(A[t].begin(), A[t].end(), 0.0);

        // Update Z
        for (int k = 0; k < SourceNum; ++k) {
            Z[t+1][k] = max(Z[t][k] + P[t][k] - MaxNum[k], 0.0);
            ZE[t+1][k] = max(ZE[t][k] + PE[t][k] - MaxNum[k], 0.0);
            ZST[t+1][k] = max(ZST[t][k] + PSTop[t][k] - MaxNum[k], 0.0);
            ZL[t+1][k] = max(ZL[t][k] + PLongest[t][k] - MaxNum[k], 0.0);
            ZAve[t+1][k] = max(ZAve[t][k] + PAve[t][k] - MaxNum[k], 0.0);
            ZRand[t+1][k] = max(ZRand[t][k] + PRand[t][k] - MaxNum[k], 0.0);
        }

        data2[t] = P[t][0];
        data3[t] = P[t][1];
        DEP[t] = PE[t][0];
        DEB[t] = PE[t][1];
        DSTOPP[t] = PSTop[t][0];
        DSTOPB[t] = PSTop[t][1];
        DLongP[t] = PLongest[t][0];
        DLongB[t] = PLongest[t][1];
        DAveP[t] = PAve[t][0];
        DAveB[t] = PAve[t][1];
        DRandP[t] = PRand[t][0];
        DRandB[t] = PRand[t][1];
    }

    // Compute averages for Throughput
    for (int t = 0; t < T; ++t) {
        ThroughputP[t] = accumulate(ThroughputP.begin(), ThroughputP.begin() + t + 1, 0.0) / (t + 1);
        ThroughputE[t] = accumulate(ThroughputE.begin(), ThroughputE.begin() + t + 1, 0.0) / (t + 1);
        ThroughputTOP[t] = accumulate(ThroughputTOP.begin(), ThroughputTOP.begin() + t + 1, 0.0) / (t + 1);
        ThroughputLong[t] = accumulate(ThroughputLong.begin(), ThroughputLong.begin() + t + 1, 0.0) / (t + 1);
        ThroughputAve[t] = accumulate(ThroughputAve.begin(), ThroughputAve.begin() + t + 1, 0.0) / (t + 1);
        ThroughputRand[t] = accumulate(ThroughputRand.begin(), ThroughputRand.begin() + t + 1, 0.0) / (t + 1);
    }

    // Output results
    cout << "平均吞吐量 " << ThroughputP[T-1] << " " << ThroughputE[T-1] << " " << ThroughputTOP[T-1] << " " << ThroughputLong[T-1] << " " << ThroughputAve[T-1] << " " << ThroughputRand[T-1] << endl;
    cout << "平均队列长度 " << accumulate(Q.begin(), Q.end(), 0.0) / (T * ShardNum) << " " << accumulate(QE.begin(), QE.end(), 0.0) / (T * ShardNum) << " " << accumulate(QST.begin(), QST.end(), 0.0) / (T * ShardNum) << " " << accumulate(QL.begin(), QL.end(), 0.0) / (T * ShardNum) << " " << accumulate(QAve.begin(), QAve.end(), 0.0) / (T * ShardNum) << " " << accumulate(QRand.begin(), QRand.end(), 0.0) / (T * ShardNum) << endl;
    cout << "平均功率损耗 " << accumulate(data2.begin(), data2.end(), 0.0) / T << " " << accumulate(DEP.begin(), DEP.end(), 0.0) / T << " " << accumulate(DSTOPP.begin(), DSTOPP.end(), 0.0) / T << " " << accumulate(DLongP.begin(), DLongP.end(), 0.0) / T << " " << accumulate(DAveP.begin(), DAveP.end(), 0.0) / T << " " << accumulate(DRandP.begin(), DRandP.end(), 0.0) / T << endl;
    cout << "平均带宽损耗 " << accumulate(data3.begin(), data3.end(), 0.0) / T << " " << accumulate(DEB.begin(), DEB.end(), 0.0) / T << " " << accumulate(DSTOPB.begin(), DSTOPB.end(), 0.0) / T << " " << accumulate(DLongB.begin(), DLongB.end(), 0.0) / T << " " << accumulate(DAveB.begin(), DAveB.end(), 0.0) / T << " " << accumulate(DRandB.begin(), DRandB.end(), 0.0) / T << endl;

    return 0;
}

std::tuple<std::vector<double>, std::vector<double>> ProcessServer::stop(std::vector<double> Q, int ShardNum)
{
    int SourceNum = 2;
    std::vector<double> MaxNum = {3300, 3000};
    std::vector<double> Weight = {5, 4};
    double alpha = 0.5;

    // Initialize B and P vectors
    std::vector<double> B(ShardNum, 0);
    std::vector<double> P(SourceNum, 0);

    // Initialize p matrix
    std::vector<std::vector<double>> p(ShardNum, std::vector<double>(SourceNum, 0));

    // Sort Q in descending order and get the corresponding indices
    std::vector<double> sortedQ = Q;
    std::sort(sortedQ.begin(), sortedQ.end(), std::greater<double>());
    std::vector<int> I(ShardNum);
    for (int i = 0; i < ShardNum; ++i) {
        auto it = std::find(Q.begin(), Q.end(), sortedQ[i]);
        I[i] = std::distance(Q.begin(), it);
    }

    // Calculate B and P
    for (int i = 0; i < std::ceil(0.5 * ShardNum); ++i) {
        for (int k = 0; k < SourceNum; ++k) {
            p[I[i]][k] = MaxNum[k] / std::ceil(0.5 * ShardNum);
            B[I[i]] += std::pow(Weight[k] * p[I[i]][k], alpha);
            P[k] += p[I[i]][k];
        }
    }

    return std::make_tuple(B, P);
}
