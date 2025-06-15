#include "resAllocateAlorgith.h"

using namespace std;

//////////////////////////////////////////////////AVERAGE/////////////////////////////////////////////////////////
/*
    int main() {
    int ShardNum = 4;
    Average(ShardNum);
    return 0;
}
*/

int alorgith::Average(int ShardNum)
{
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 1;
    int SlotsInterval = 1;

    vector<double> B(ShardNum, 0);
    vector<double> P(SourceNum, 0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0));

    // Average Res. Allocation
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = MaxNum[k] / ShardNum;
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Output the results
    cout << "Resource Allocation:" << endl;
    cout << "B: ";
    for (double b : B)
    {
        cout << b << " ";
    }
    cout << endl;
    cout << "P: ";
    for (double p_val : P)
    {
        cout << p_val << " ";
    }
    cout << endl;

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////DUALASCENT//////////////////////////////////////////////////////

int alorgith::Dualascent()
{
    vector<double> x = {100, -120}; // Decision variable initialization
    vector<double> lambda = {0, 0}; // Lagrange multipliers initialization
    int k = 1;
    vector<vector<double>> G_v;      // Gradient vector history
    vector<vector<double>> x_v;      // Decision variable history
    vector<vector<double>> lambda_v; // Lagrange multipliers history
    vector<double> L_v;              // Lagrangian function history
    vector<double> f_v;              // Objective function history
    double tol = 1e-5;
    double t_lambda = 0.1; // Lagrange multiplier update step size
    double t_x = 0.1;      // Decision variable update step size
    int max_iteration = 10000;

    for (int i = 1; i <= max_iteration; ++i)
    {
        // Iterative update of decision variables x
        x[0] -= t_x * (4 * (x[0] - 1) - lambda[0]);
        x[1] -= t_x * (2 * (x[1] + 2) - lambda[1]);

        // Iterative update of Lagrange multipliers lambda
        vector<double> Grad_f = {2 - x[0], -x[1]};
        lambda[0] = max(lambda[0] + t_lambda * Grad_f[0], 0.0);
        lambda[1] = max(lambda[1] + t_lambda * Grad_f[1], 0.0);

        // Calculate objective function and Lagrangian function
        double f = 2 * pow((x[0] - 1), 2) + pow((x[1] + 2), 2);
        double L = f + lambda[0] * (2 - x[0]) + lambda[1] * (-x[1]);

        // Record historical updates
        G_v.push_back(Grad_f);
        x_v.push_back(x);
        lambda_v.push_back(lambda);
        f_v.push_back(f);
        L_v.push_back(L);

        // Termination condition check
        if (i > 2 && abs(f - L) < tol)
            break;

        k++;
    }

    if (k == max_iteration)
    {
        cout << "Exceeded maximum iteration limit!" << endl;
    }

    cout << "Number of iterations: " << k << endl;
    cout << "Optimal point: [" << x[0] << ", " << x[1] << "]" << endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////DUALASCENTFL//////////////////////////////////////
int alorgith::Dualascentfl()
{
    vector<double> x = {-10, 10};         // Decision variable initialization
    vector<double> lambda = {1, 1, 1, 1}; // Lagrange multipliers initialization
    int k = 1;
    vector<vector<double>> G_v;      // Gradient vector history
    vector<vector<double>> x_v;      // Decision variable history
    vector<vector<double>> lambda_v; // Lagrange multipliers history
    vector<double> L_v;              // Lagrangian function history
    vector<double> f_v;              // Objective function history
    double tol = 1e-5;
    double t_lambda = 0.01; // Lagrange multiplier update step size
    double epsilon = 0.1;
    double t_x_1 = 0.1; // Decision variable x1 update step size
    double t_x_2 = 0.1; // Decision variable x2 update step size
    int max_iteration = 10000;

    for (int i = 1; i <= max_iteration; ++i)
    {
        // Iterative update of decision variables x
        x[0] -= t_x_1 * (-pow(x[0], -2) + 2 * x[0] - lambda[0] + lambda[1]);
        x[1] -= t_x_2 * (-pow(x[1], -2) + 2 * x[1] - lambda[2] + lambda[3]);

        // Iterative update of Lagrange multipliers lambda
        vector<double> Grad_f = {-x[0], x[0] - 1, -x[1], x[1] - 1};
        for (int j = 0; j < 4; ++j)
        {
            lambda[j] = max(lambda[j] + t_lambda * Grad_f[j], 0.0);
        }

        // Calculate objective function and Lagrangian function
        double f = 1 / x[0] + pow(x[0], 2) + 1 / x[1] + pow(x[1], 2);
        double L = f + lambda[0] * (-x[0]) + lambda[1] * (x[0] - 1) + lambda[2] * (-x[1]) + lambda[3] * (x[1] - 1);

        // Record historical updates
        G_v.push_back(Grad_f);
        x_v.push_back(x);
        lambda_v.push_back(lambda);
        f_v.push_back(f);
        L_v.push_back(L);

        // Termination condition check
        if (i > 2 && abs(f - L) < tol && Grad_f[0] <= epsilon && Grad_f[1] <= epsilon && Grad_f[2] <= epsilon && Grad_f[3] <= epsilon)
            break;

        k++;
    }

    if (k == max_iteration)
        cout << "Exceeded maximum iteration limit!" << endl;

    cout << "Number of iterations: " << k << endl;
    cout << "Optimal point: [" << x[0] << ", " << x[1] << "]" << endl;

    return 0;
}

//////////////////////////////////////////////////////////ELASTIC////////////////////////////////////////////////////////////////////////////////////////
pair<vector<double>, vector<double>> alorgith::Elastic(double Q, vector<double> Z, double V, int ShardNum)
{
    // Define parameters
    int SourceNum = 2;
    vector<double> MaxNum = {3300, 3000}; // Maximum resources
    vector<double> Weight = {5, 4};       // Resource weights
    double alpha = 0.5;
    double RTX = 5;
    double BlockSize = 10;
    double BlockInterval = 1;
    double SlotsInterval = 1;

    // Initialize B and P vectors
    vector<double> B(ShardNum, 0.0);
    vector<double> P(SourceNum, 0.0);

    // Initialize p matrix
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0.0));

    // Calculate resource allocation
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = pow(((V + Z[k]) / (alpha * pow(Weight[k], alpha) * (Q + RTX * V))), 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Return B and P vectors
    return make_pair(B, P);
}

int alorgith::invoke_elastic()
{
    // Example usage
    double Q = 0;              // Current queue length
    vector<double> Z = {0, 0}; // Dummy values for Z
    double V = 30;             // Queue length parameter
    int ShardNum = 4;          // Number of shards

    // Perform Elastic resource allocation
    pair<vector<double>, vector<double>> result = Elastic(Q, Z, V, ShardNum);

    // Output B and P vectors
    cout << "B vector:" << endl;
    for (auto b : result.first)
    {
        cout << b << " ";
    }
    cout << endl;

    cout << "P vector:" << endl;
    for (auto p : result.second)
    {
        cout << p << " ";
    }
    cout << endl;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////LONGEST//////////////////////////////////////////////////////////////

int alorgith::Longest(vector<int> &Q, int ShardNum, vector<int> &B, vector<int> &P)
{
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;

    B.assign(ShardNum, 0);
    P.assign(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));

    // Sort queues in descending order
    vector<pair<int, int>> queue_indices;
    for (int i = 0; i < ShardNum; ++i)
    {
        queue_indices.push_back({Q[i], i});
    }
    sort(queue_indices.rbegin(), queue_indices.rend());

    // Allocate resources to the shard with the longest queue
    for (int k = 0; k < SourceNum; ++k)
    {
        int shard_index = queue_indices[0].second;
        p[shard_index][k] = MaxNum[k];
        B[shard_index] += pow((Weight[k] * p[shard_index][k]), alpha);
        P[k] = MaxNum[k];
    }

    return 0;
}

int alorgith::invoke_longest()
{
    int ShardNum = 4;
    vector<int> Q = {10, 20, 15, 25}; // Example queue lengths

    // Perform resource allocation
    vector<int> B, P;
    Longest(Q, ShardNum, B, P);

    // Print the allocated resources
    cout << "Allocated resources:\n";
    cout << "B: ";
    for (int i = 0; i < ShardNum; ++i)
    {
        cout << B[i] << " ";
    }
    cout << "\n";
    cout << "P: ";
    for (int i = 0; i < P.size(); ++i)
    {
        cout << P[i] << " ";
    }
    cout << "\n";

    return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////RANDOM////////////////////////////////////////////////////////////////////////////////////////

int alorgith::Random(int ShardNum, vector<int> &B, vector<int> &P)
{
    int SourceNum = 2;
    vector<int> MaxNum = {3300, 3000};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;

    B.assign(ShardNum, 0);
    P.assign(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));

    // Generate random maximum resource values
    MaxNum[0] = rand() % 1500 + 1000; // Random value between 1000 and 2500
    MaxNum[1] = rand() % 1001 + 1000; // Random value between 1000 and 2000

    // Allocate resources randomly
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = rand() % (MaxNum[k] + 1); // Random value between 0 and MaxNum[k]
            B[i] += pow((Weight[k] * p[i][k]), alpha);
            P[k] += p[i][k];
        }
    }

    return 0;
}

int alorgith::invokd_random()
{
    int ShardNum = 4;

    // Perform random resource allocation
    vector<int> B, P;
    Random(ShardNum, B, P);

    // Print the allocated resources
    cout << "Allocated resources:\n";
    cout << "B: ";
    for (int i = 0; i < ShardNum; ++i)
    {
        cout << B[i] << " ";
    }
    cout << "\n";
    cout << "P: ";
    for (int i = 0; i < P.size(); ++i)
    {
        cout << P[i] << " ";
    }
    cout << "\n";

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////resallocation//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
需要判断不满足约束的采用拉格朗日，满足约束的不用。设置一个标志位，标志位为0时直接计算，不满足约束后将标志位置为1

第一种均衡是资源充足，所有条件都满足

第二种均衡是资源不足，通过对偶分解法（对偶上升法）
先将所有都看作是不满足约束的，然后再单独把不满足约束的挑出来，满足约束的就采用第一种均衡，不满足约束的再使用第二章均衡
或者部分情况，所有都当作第二种情况讨论，看作是两个不等式约束，然后对比之间有什么差比
首先是都不满足约束，那么就有一个资源等式约束和一个块间隔的不等式约束
需要更新的有p(i)(k),lambda(i),gamma(k)

*/

int alorgith::resallocation(vector<int> &Q, int V)
{

    /*
        int main()
        {
            vector<int> Q = {0, 0, 0, 0}; // Initialize Q vector with zeros
            int V = 50;                   // Set V value

            resallocation(Q, V);

            return 0;
        }
    */

    const int ShardNum = 4;
    const int SourceNum = 2;
    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 5;
    int SlotsInterval = 8;
    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0));
    vector<double> lambda(ShardNum, 0);
    vector<double> gamma(SourceNum, 0);
    double updatestepl = 0.1;
    double updatestepg = 0.1;
    double Lk = 0;
    double Li = 0;
    double f = 0;
    vector<double> L_v;        // Record Lagrangian function history
    vector<double> f_v;        // Record original function history
    int iter = 1;              // Iteration counter
    double tol = 1e-5;         // Used to limit the gap between the original function and the objective function
    int max_iteration = 10000; // Maximum number of iterations
    vector<int> flag1(SourceNum, 0);

    for (int i = 0; i < ShardNum; i++)
    {
        for (int k = 0; k < SourceNum; k++)
        {
            p[i][k] = pow(V / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    for (int k = 0; k < SourceNum; k++)
    {
        if (P[k] > MaxNum[k])
        {
            cout << "Exceeds resource constraint" << endl;
            flag1[k] = 1;
        }
    }

    cout << "Sufficient resources, resource allocation completed" << endl;

    vector<int> GB(ShardNum, 0);

    for (int j = 1; j <= max_iteration; j++)
    {
        fill(B.begin(), B.end(), 0);
        fill(GB.begin(), GB.end(), 0);
        f = 0;
        Li = 0;
        Lk = 0;

        for (int i = 0; i < ShardNum; i++)
        {
            for (int k = 0; k < SourceNum; k++)
            {
                if (flag1[k] == 1)
                {
                    p[i][k] = pow((V - gamma[k]) / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V + lambda[i])), 1 / (alpha - 1));
                    GB[i] += pow(Weight[k] * p[i][k], alpha);
                }
                B[i] += pow(Weight[k] * p[i][k], alpha);
            }
            lambda[i] = max(lambda[i] - updatestepl * (B[i] - BlockSize * BlockInterval / SlotsInterval), 0.0);
        }

        for (int k = 0; k < SourceNum; k++)
        {
            if (flag1[k] == 1)
            {
                P[k] = 0;
                for (int i = 0; i < ShardNum; i++)
                {
                    P[k] += p[i][k];
                }
                gamma[k] -= updatestepg * (P[k] - MaxNum[k]);
                Lk += gamma[k] * (P[k] - MaxNum[k]);
            }
        }

        for (int i = 0; i < ShardNum; i++)
        {
            f += (Q[i] + V * RTX) * GB[i] - V * accumulate(p[i].begin(), p[i].end(), 0.0);
            Li += lambda[i] * (B[i] - BlockSize * BlockInterval / SlotsInterval);
        }

        double L = f + Lk + Li; // Lagrangian function
        f_v.push_back(f);
        L_v.push_back(L);

        if (iter > 2 && abs(f - L) < tol)
        {
            break;
        }
        iter++;
    }

    cout << "Insufficient resources, Lagrangian allocation completed" << endl;
    return 0;
}

/*
    vector<int> Q = {1, 2, 3, 4}; // Example values for Q
    int V = 100; // Example value for V
    resallocation(Q, V);
    return 0;
*/
int alorgith::resallocation_lagrange(vector<int> Q, int V)
{
    // Initialize parameters
    int ShardNum = 4;
    int SourceNum = 2;
    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 5;
    int SlotsInterval = 8;
    double updatestepl = 0.1;
    double updatestepg = 0.1;
    double tol = 1e-5;
    int max_iteration = 10000;

    // Define variables
    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));
    vector<int> flag1(SourceNum, 0);

    // Resource allocation
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = pow(V / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Check constraints
    for (int k = 0; k < SourceNum; ++k)
    {
        if (P[k] > MaxNum[k])
        {
            cout << "Exceeded resource constraint: " << k << endl;
            flag1[k] = 1;
        }
    }

    // Resource allocation loop
    for (int j = 0; j < max_iteration; ++j)
    {
        // Resource allocation
        for (int i = 0; i < ShardNum; ++i)
        {
            for (int k = 0; k < SourceNum; ++k)
            {
                if (flag1[k] == 1)
                {
                    p[i][k] = pow((V - P[k]) / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
                    B[i] += pow(Weight[k] * p[i][k], alpha);
                }
            }
        }

        // Update Lagrange multipliers
        for (int i = 0; i < ShardNum; ++i)
        {
            for (int k = 0; k < SourceNum; ++k)
            {
                if (flag1[k] == 1)
                {
                    B[i] += pow(Weight[k] * p[i][k], alpha);
                }
            }
        }

        // Check convergence
        double f = 0;
        for (int i = 0; i < ShardNum; ++i)
        {
            f += (Q[i] + V * RTX) * B[i] - V * P[i];
        }
        if (abs(f) < tol)
        {
            break;
        }
    }

    // Output
    cout << "Resource allocation: " << endl;
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            cout << p[i][k] << " ";
        }
        cout << endl;
    }

    return 0;
}


/*
    vector<int> Q = {1, 2, 3, 4}; // Example values for Q
    int V = 100; // Example value for V
    int ShardNum = 4; // Example value for ShardNum
    resallocation_without_blockinterval(Q, V, ShardNum);
*/

int alorgith::resallocation_without_blockinterval(vector<int> Q, int V, int ShardNum)
{
        // Initialize parameters
    int SourceNum = 2;
    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};
    double alpha = 0.5;
    int RTX = 5;
    int BlockSize = 10;
    int BlockInterval = 5;
    int SlotsInterval = 8;
    double updatestepl = 0.1;
    double updatestepg = 0.1;
    double tol = 1e-5;
    int max_iteration = 10000;

    // Define variables
    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));
    vector<int> flag1(SourceNum, 0);
    vector<int> gamma(SourceNum, 0); // Initialize gamma vector

    // Resource allocation
    for (int i = 0; i < ShardNum; ++i) {
        for (int k = 0; k < SourceNum; ++k) {
            p[i][k] = pow(V / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Check constraints
    for (int k = 0; k < SourceNum; ++k) {
        if (P[k] > MaxNum[k]) {
            cout << "Exceeded resource constraint: " << k << endl;
            flag1[k] = 1;
        }
    }

    // Resource allocation loop
    for (int j = 0; j < max_iteration; ++j) {
        vector<int> GB(ShardNum, 0);
        double f = 0;
        double Lk = 0;

        for (int i = 0; i < ShardNum; ++i) {
            for (int k = 0; k < SourceNum; ++k) {
                if (flag1[k] == 1) {
                    p[i][k] = pow((V - gamma[k]) / (alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V)), 1 / (alpha - 1));
                    GB[i] += pow(Weight[k] * p[i][k], alpha);
                }
                B[i] += pow(Weight[k] * p[i][k], alpha);
            }
        }

        for (int i = 0; i < ShardNum; ++i) 
        {
            f += (Q[i] + V * RTX) * GB[i] - V * P[i];
        }

        if (abs(f) < tol) {
            break;
        }
    }

    // Output
    cout << "Resource allocation: " << endl;
    for (int i = 0; i < ShardNum; ++i) 
    {
        for (int k = 0; k < SourceNum; ++k) {
            cout << p[i][k] << " ";
        }
        cout << endl;
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////