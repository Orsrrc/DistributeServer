#ifndef __RESALLOCATEALORGITH__H_

#define __RESALLOCATEALORGITH__H_

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <numeric> //accumulate
#include "../Common.hpp"

class alorgith
{
    int Average(int ShardNum);

    int Dualascent();

    int Dualascentfl();

    pair<vector<double>, vector<double>> Elastic(double Q, vector<double> Z, double V, int ShardNum);

    int invoke_elastic();

    int Longest(vector<int> &Q, int ShardNum, vector<int> &B, vector<int> &P);
    int invoke_longest();

    int Random(int ShardNum, vector<int> &B, vector<int> &P);

    int invokd_random();


    int resallocation(vector<int>& Q, int V);
    int resallocation_lagrange(vector<int> Q, int V);
    
    int resallocation_without_blockinterval(vector<int> Q, int V, int ShardNum);


};

#endif //__RESALLOCATEALORGITH__H_