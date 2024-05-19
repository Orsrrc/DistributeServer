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

int alorgith::Top_S(int ShardNum, int SourceNum, double alpha)
{
    std::vector<double> MaxNum = {3300, 3000};
    std::vector<double> Weight = {5, 4};
    vector<double> B(ShardNum, 0.0);
    // Iterate over the range 1 to 0.5*ShardNum
    for (int i = 1; i <= 0.5 * ShardNum; ++i)
    {
        // Iterate over the SourceNum
        for (int k = 1; k <= SourceNum; ++k)
        {
            // Calculate p(i,k)
            double p_ik = MaxNum[k - 1] / (0.5 * ShardNum); // Adjusting indices since C++ uses 0-based indexing
            // Update B(i)
            B[i - 1] += pow(Weight[k - 1] * p_ik, alpha); // Adjusting indices since C++ uses 0-based indexing
        }
    }
    return OK;
}

int alorgith::Average(int ShardNum, int SourceNum, double alpha)
{
    std::vector<double> MaxNum = {3300, 3000};
    std::vector<double> Weight = {5, 4};
    vector<double> B(ShardNum, 0.0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0.0));
    // Iterate over i from 1 to ShardNum
    for (int i = 1; i <= ShardNum; ++i)
    {
        // Iterate over k from 1 to SourceNum
        for (int k = 1; k <= SourceNum; ++k)
        {
            // Calculate p(i,k)
            p[i - 1][k - 1] = MaxNum[k - 1] / static_cast<double>(ShardNum); // Adjusting indices and casting to double for division
            // Update B(i)
            B[i - 1] += pow(Weight[k - 1] * p[i - 1][k - 1], alpha); // Adjusting indices and using pow function for exponentiation
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////DUALASCENT//////////////////////////////////////////////////////

int alorgith::Dualascent(int max_iteration,
                         double tol,
                         double t_lambda, // Update step size for Lagrange multipliers
                         double t_x       // Update step size for decision variables

)

{

    // Initialize variables
    vector<double> x = {100, -120}; // Decision variable initialization
    vector<double> lambda = {0, 0}; // Lagrange multipliers initialization
    vector<double> Grad_f(2);
    vector<double> G_v, lambda_v, x_v, L_v, f_v;
    int k = 1;

    // Perform iterations
    for (int i = 1; i <= max_iteration; ++i)
    {
        // Update decision variables x
        x[0] -= t_x * (4 * (x[0] - 1) - lambda[0]);
        x[1] -= t_x * (2 * (x[1] + 2) - lambda[1]);

        // Update Lagrange multipliers lambda
        Grad_f[0] = 2 - x[0];
        Grad_f[1] = -x[1];
        lambda[0] = max(lambda[0] + t_lambda * Grad_f[0], 0.0);
        lambda[1] = max(lambda[1] + t_lambda * Grad_f[1], 0.0);

        // Calculate objective function value and Lagrangian
        double f = 2 * pow(x[0] - 1, 2) + pow(x[1] + 2, 2);
        double L = f + lambda[0] * (2 - x[0]) + lambda[1] * (-x[1]);

        // Record historical update results
        G_v.insert(G_v.end(), Grad_f.begin(), Grad_f.end());
        x_v.insert(x_v.end(), x.begin(), x.end());
        lambda_v.insert(lambda_v.end(), lambda.begin(), lambda.end());
        f_v.push_back(f);
        L_v.push_back(L);

        // Termination condition
        if (i > 2 && abs(f - L) < tol)
            break;
        k = i;
    }

    if (k == max_iteration)
        cout << "Exceeded maximum number of iterations!" << endl;

    cout << "Number of iterations: " << k << endl;
    cout << "Optimal point: [" << x[0] << ", " << x[1] << "]" << endl;
    cout << "Optimal value: " << L_v.back() << endl;
    return OK;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////DUALASCENTFL//////////////////////////////////////
int alorgith::Dualascentfl(
    int max_iteration,
    double tol,
    double t_lambda, // Update step size for Lagrange multipliers
    double epsilon,
    double t_x_1, // Update step size for decision variable x1
    double t_x_2  // Update step size for decision variable x2

)
{
    // Initialize variables
    vector<double> x = {-10, 10};         // Decision variable initialization
    vector<double> lambda = {1, 1, 1, 1}; // Lagrange multipliers initialization
    vector<double> Grad_f(4);
    vector<double> G_v, lambda_v, x_v, L_v, f_v;

    int k = 1;
    // Perform iterations
    for (int i = 1; i <= max_iteration; ++i)
    {
        // Update decision variables x
        x[0] -= t_x_1 * (-1 / pow(x[0], 2) + 2 * x[0] - lambda[0] + lambda[1]);
        x[1] -= t_x_2 * (-1 / pow(x[1], 2) + 2 * x[1] - lambda[2] + lambda[3]);

        // Update Lagrange multipliers lambda
        Grad_f[0] = -x[0];
        Grad_f[1] = x[0] - 1;
        Grad_f[2] = -x[1];
        Grad_f[3] = x[1] - 1;
        for (int j = 0; j < 4; ++j)
        {
            lambda[j] = max(lambda[j] + t_lambda * Grad_f[j], 0.0);
        }

        // Calculate objective function value and Lagrangian
        double f = 1 / x[0] + pow(x[0], 2) + 1 / x[1] + pow(x[1], 2);
        double L = f + lambda[0] * (-x[0]) + lambda[1] * (x[0] - 1) + lambda[2] * (-x[1]) + lambda[3] * (x[1] - 1);

        // Record historical update results
        G_v.insert(G_v.end(), Grad_f.begin(), Grad_f.end());
        x_v.insert(x_v.end(), x.begin(), x.end());
        lambda_v.insert(lambda_v.end(), lambda.begin(), lambda.end());
        f_v.push_back(f);
        L_v.push_back(L);

        // Termination condition
        if (k > 2 && abs(f - L) < tol && Grad_f[0] <= epsilon && Grad_f[1] <= epsilon && Grad_f[2] <= epsilon && Grad_f[3] <= epsilon)
            break;

        k = i;
    }

    if (k == max_iteration)
        cout << "Exceeded maximum number of iterations!" << endl;

    cout << "Number of iterations: " << k << endl;
    cout << "Optimal point: [" << x[0] << ", " << x[1] << "]" << endl;
    cout << "Optimal value: " << L_v.back() << endl;

    return OK;
}

//////////////////////////////////////////////////////////ELASTIC////////////////////////////////////////////////////////////////////////////////////////
int alorgith::Elastic(int ShardNum,
                      int SourceNum,
                      double alpha,
                      double RTX,
                      double V,
                      double Z1,
                      double Z2)
{
    // Given parameters
    vector<double> MaxNum = {3300, 3000};

    vector<double> Weight = {5, 4};

    // Initialize variables
    vector<double> B(ShardNum, 0.0);
    vector<double> P(SourceNum, 0.0);
    vector<double> Q(ShardNum, 0.0); // Assuming Q is defined elsewhere

    // Calculate values
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0.0));

    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            double numerator = (V + (k == 0 ? Z1 : Z2));
            double denominator = alpha * pow(Weight[k], alpha) * (Q[i] + RTX * V);
            p[i][k] = pow(numerator / denominator, 1 / (alpha - 1));
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }
    // Output results or use them as needed
    return OK;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////LONGEST//////////////////////////////////////////////////////////////

int alorgith::Longest(int SourceNum, int ShardNum, double alpha)
{
    // Given parameters
    vector<double> MaxNum = {3300, 3000};
    int SourceNum = 2;
    vector<double> Weight = {5, 4};
    double alpha = 0.5;

    int ShardNum = 10;
    vector<double> Q(ShardNum); // Assuming Q is defined elsewhere

    // Initialize variables
    vector<double> B(ShardNum, 0.0);
    vector<double> P(SourceNum, 0.0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0.0));

    // Sort Q in descending order and get the indices
    vector<int> I(ShardNum);
    iota(I.begin(), I.end(), 0); // Fill I with indices 0, 1, 2, ..., ShardNum - 1
    sort(I.begin(), I.end(), [&](int i, int j)
         { return Q[i] > Q[j]; });

    // Assign values based on sorted Q
    for (int k = 0; k < SourceNum; ++k)
    {
        p[I[0]][k] = MaxNum[k];
        B[I[0]] += pow(Weight[k] * p[I[0]][k], alpha);
        P[k] = MaxNum[k];
    }

    // Output results or use them as needed
    return OK;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////RANDOM////////////////////////////////////////////////////////////////////////////////////////

int alorgith::Random(int ShardNum = 24,
                     int SourceNum = 2,
                     double alpha = 0.5,
                     double RTX = 5,
                     double BlockSize = 1,
                     double BlockInterval = 1,
                     double SlotsInterval = 1)
{
    // Given parameters

    vector<int> MaxNum = {3300, 3000};
    vector<int> Weight = {5, 4};

    // Initialize variables
    vector<double> B(ShardNum, 0.0);
    vector<double> P(SourceNum, 0.0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0.0));

    // Generate random MaxNum values
    MaxNum[0] = rand() % (2500 - 1000 + 1) + 1000;
    MaxNum[1] = rand() % (2000 - 1000 + 1) + 1000;

    // Generate random values for A and normalize
    vector<double> A(ShardNum);
    double sumA = 0.0;
    for (int i = 0; i < ShardNum; ++i)
    {
        A[i] = static_cast<double>(rand()) / RAND_MAX; // Generate a random number between 0 and 1
        sumA += A[i];
    }
    for (int i = 0; i < ShardNum; ++i)
    {
        A[i] /= sumA; // Normalize A
    }

    // Calculate p, B, and P
    for (int i = 0; i < ShardNum; ++i)
    {
        for (int k = 0; k < SourceNum; ++k)
        {
            p[i][k] = MaxNum[k] * A[i];
            B[i] += pow(Weight[k] * p[i][k], alpha);
            P[k] += p[i][k];
        }
    }

    // Output results or use them as needed
    return OK;
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

int alorgith::resallocation(
    int max_iteration, // Maximum number of iterations
    const int ShardNum,
    const int SourceNum,
    double tol, // Used to limit the gap between the original function and the objective function
    double alpha,
    int RTX,
    int BlockSize,
    int BlockInterval,
    int SlotsInterval,
    double updatestepl,
    double updatestepg,
    double Lk,
    double Li,
    double f,
    int iter,
    int V)
{

    /*
        int main()
        {

            int V = 50;                   // Set V value

            resallocation(Q, V);

            return 0;
        }
    */

    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};

    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<double>> p(ShardNum, vector<double>(SourceNum, 0));
    vector<double> lambda(ShardNum, 0);
    vector<double> gamma(SourceNum, 0);

    vector<double> Q(ShardNum, 0.0); // Initialize Q vector with zeros

    vector<double> L_v; // Record Lagrangian function history
    vector<double> f_v; // Record original function history

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
int alorgith::resallocation_lagrange(int ShardNum,
                                     int SourceNum,
                                     double alpha,
                                     int RTX,
                                     int BlockSize,
                                     int BlockInterval,
                                     int SlotsInterval,
                                     double updatestepl,
                                     double updatestepg,
                                     double tol,
                                     int max_iteration,
                                     int V)
{
    // Initialize parameters
    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};

    // Define variables
    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));
    vector<int> flag1(SourceNum, 0);
    vector<double> Q(ShardNum, 0.0); // Initialize Q vector with zeros
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

int alorgith::resallocation_without_blockinterval(
    int max_iteration,
    int SourceNum,
    int ShardNum,
    double alpha,
    int RTX,
    int BlockSize,
    int BlockInterval,
    int SlotsInterval,
    double updatestepl,
    double updatestepg,
    double tol,
    int V)
{
    // Initialize parameters
    vector<int> MaxNum = {200, 150};
    vector<int> Weight = {5, 4};

    // Define variables
    vector<int> B(ShardNum, 0);
    vector<int> P(SourceNum, 0);
    vector<vector<int>> p(ShardNum, vector<int>(SourceNum, 0));
    vector<int> flag1(SourceNum, 0);
    vector<int> gamma(SourceNum, 0); // Initialize gamma vector
    vector<double> Q(ShardNum, 0.0); // Initialize Q vector with zeros
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
        vector<int> GB(ShardNum, 0);
        double f = 0;
        double Lk = 0;

        for (int i = 0; i < ShardNum; ++i)
        {
            for (int k = 0; k < SourceNum; ++k)
            {
                if (flag1[k] == 1)
                {
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
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////