#include "dualascent.h"


int dualascent::dualdecomposition_allocate()
{
    // 初始化参数和变量
    std::vector<double> x = {100, -120};
    std::vector<double> lambda(2, 0); // 初始拉格朗日乘子为0
    double t_lambda = 0.1;
    double t_x = 0.1;
    double tol = 1e-5;
    int max_iteration = 10000;
    std::vector<double> G_v, lambda_v, x_v, L_v, f_v;

    // 开始迭代
    for (int k = 1; k <= max_iteration; ++k)
    {
        // 迭代更新决策变量 x
        x[0] -= t_x * (4 * (x[0] - 1) - lambda[0]);
        x[1] -= t_x * (2 * (x[1] + 2) - lambda[1]);

        // 迭代更新拉格朗日乘子 lambda
        std::vector<double> Grad_f = {2 - x[0], -x[1]};
        lambda[0] = std::max(lambda[0] + t_lambda * Grad_f[0], 0.0);
        lambda[1] = std::max(lambda[1] + t_lambda * Grad_f[1], 0.0);

        // 计算目标函数值和拉格朗日函数值
        double f = 2 * pow(x[0] - 1, 2) + pow(x[1] + 2, 2);
        double L = f + lambda[0] * (2 - x[0]) + lambda[1] * (-x[1]);

        // 记录历史更新结果
        G_v.push_back(Grad_f[0]);
        G_v.push_back(Grad_f[1]);
        x_v.push_back(x[0]);
        x_v.push_back(x[1]);
        lambda_v.push_back(lambda[0]);
        lambda_v.push_back(lambda[1]);
        f_v.push_back(f);
        L_v.push_back(L);

        // 终止条件判断
        if (k > 2 && abs(f - L) < tol)
        {
            break;
        }
    }

    // 输出结果
    std::cout << "迭代次数为：" << G_v.size() / 2 << "次" << std::endl;
    std::cout << "最优值点为：" << std::endl;
    std::cout << "x1: " << x[0] << std::endl;
    std::cout << "x2: " << x[1] << std::endl;

    return 0;
}