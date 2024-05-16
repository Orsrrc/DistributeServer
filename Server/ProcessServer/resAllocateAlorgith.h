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
    int Top_S(int ShardNum = 10, int SourceNum = 2, double alpha = 0.5);

    int Average(int ShardNum = 10, int SourceNum = 2, double alpha = 0.5);

    int Dualascent(int max_iteration = 10000, double tol = 1e-5, double t_lambda = 0.1, double t_x = 0.1);

    int Dualascentfl(int max_iteration = 10000,
                     double tol = 1e-5,
                     double t_lambda = 0.01, // Update step size for Lagrange multipliers
                     double epsilon = 0.1,
                     double t_x_1 = 0.1, // Update step size for decision variable x1
                     double t_x_2 = 0.1  // Update step size for decision variable x2);
    );
    int Elastic(int SourceNum = 2,
                int ShardNum = 10, // Assuming ShardNum is defined elsewhere
                double alpha = 0.5,
                double RTX = 5, // Assuming RTX is defined elsewhere
                double V = 0,   // Assuming V is defined elsewhere
                double Z1 = 0,  // Assuming Z1 and Z2 are defined elsewhere
                double Z2 = 0);

    int Longest(int SourceNum = 2,
                int ShardNum = 10, // Assuming ShardNum is defined elsewhere
                double alpha = 0.5);

    int Random(int ShardNum = 24,
               int SourceNum = 2,
               double alpha = 0.5,
               double RTX = 5,
               double BlockSize = 1,
               double BlockInterval = 1,
               double SlotsInterval = 1);

    int resallocation(
        int max_iteration = 10000, // Maximum number of iterations
        const int ShardNum = 4,
        const int SourceNum = 2,
        double tol = 1e-5, // Used to limit the gap between the original function and the objective function
        double alpha = 0.5,
        int RTX = 5,
        int BlockSize = 10,
        int BlockInterval = 5,
        int SlotsInterval = 8,
        double updatestepl = 0.1,
        double updatestepg = 0.1,
        double Lk = 0,
        double Li = 0,
        double f = 0,
        int iter = 1, // Iteration counter
        int V);
    int resallocation_lagrange(int ShardNum = 4,
                               int SourceNum = 2,
                               double alpha = 0.5,
                               int RTX = 5,
                               int BlockSize = 10,
                               int BlockInterval = 5,
                               int SlotsInterval = 8,
                               double updatestepl = 0.1,
                               double updatestepg = 0.1,
                               double tol = 1e-5,
                               int max_iteration = 10000,
                               int V);

    int resallocation_without_blockinterval(int max_iteration = 10000,
                                            int SourceNum = 2,
                                            int ShardNum = 4,
                                            double alpha = 0.5,
                                            int RTX = 5,
                                            int BlockSize = 10,
                                            int BlockInterval = 5,
                                            int SlotsInterval = 8,
                                            double updatestepl = 0.1,
                                            double updatestepg = 0.1,
                                            double tol = 1e-5,
                                            int V);
};

#endif //__RESALLOCATEALORGITH__H_