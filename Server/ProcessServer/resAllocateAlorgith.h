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
public:
    int Top_(int ShardNum, int SourceNum, const std::vector<int>& MaxNum, const std::vector<int>& Weight, double alpha, std::vector<double>& B);

    int Average(int ShardNum, int SourceNum, const std::vector<int>& MaxNum, const std::vector<int>& Weight, double alpha, std::vector<double>& B, std::vector<std::vector<double>>& p);

    int Dualascent();

    int Dualascentfl();

    int Elastic();



    int Longest(vector<int> &Q, int ShardNum, vector<int> &B, vector<int> &P);
    int invoke_longest();

    int Random(int ShardNum, vector<int> &B, vector<int> &P);



    int resallocation(vector<int> &Q, int V);
    int resallocation_lagrange(vector<int> Q, int V);

    int resallocation_without_blockinterval(vector<int> Q, int V, int ShardNum);
};

#endif //__RESALLOCATEALORGITH__H_