#include "dualascent.h"

/*

       %记录历史更新结果
%向量合并，不许换行的话就不加；
f_v = [f_v f];
L_v = [L_v L];
%终止条件判断 %终止条件可以是最大迭代次数，可以是所有向量保持不变，还可以是拉格朗日与原函数之间的差值是否足够小
if (iter>2) &&( abs( f - L ) < tol )  % k == 5000 %k>3&&(f_v(k)-f_v(k-1)<tol)
  break;
end
iter=iter+1;
*/


int dualascent::dualdecomposition_allocate(double maxIteration,
                                           std::vector<int> shardSet, // the set of shard ID
                                           std::map<int, std::string> resourceSet,
                                           double penltyWeight,
                                           double alpha,
                                           double reward,
                                           double shardLength)
{

    double allocate = 0;
    double TX = 0;
    double useage = 0;

    double lamba = 0;

    double updatestep = 0;

    double blockInterval = 0;

    double slotsInterval = 0;

    double blockSize = 0;

    double gamma = 0;

    double updatestepg = 0;

    double LK = 0;

    double f = 0;

    double Li = 0;

    double L = 0;

    double f_v = 0;

    double L_v = 0;

    double tol = 0;

    for (int iter = 0; iter < maxIteration; iter++)
    {
        for (int i = 0; shardSet[i] != NULL; i++)
        {
            for (auto iterator = resourceSet.begin(); iterator != resourceSet.end(); iterator++)
            {
                allocate = ((penltyWeight - getGamma(iterator->first)) / (alpha * pow((getResWeight(iterator->first)), alpha) * (getShardLength(shardSet[i]))) + pow(reward * penltyWeight + getLamba(shardSet[i]), (1 / (alpha - 1))));
                TX = getShardTX(shardSet[i]) + (getResWeight(iterator->first) * allocate);

                useage = getResUsage(iterator->first) + allocate;

                setResUseage(iterator->first, useage);                  // update resource useage P(k)
                setResAllocate(shardSet[i], iterator->first, allocate); // update resource allocate p(i, k)
                setShardTX(shardSet[i], TX);
            }

            lamba = max(getLamba(shardSet[i]) - updatestep * (getShardTX(shardSet[i]) - (blockSize * blockInterval / slotsInterval)), 0);

            setLamba(shardSet[i], lamba);
        }

        for (auto iterator = resourceSet.begin(); iterator != resourceSet.end(); iterator++)
        {

            gamma = getGamma(iterator->first) - updatestepg * (getResUsage(iterator->first) - getResMax(iterator->first));

            LK = LK + getGamma(iterator->first) - (getResUsage(iterator->first) - getResMax(iterator->first));
        }

        for (int i = 0; shardSet[i] != 0; i++)
        {
            f = f + (getShardLength(shardSet[i]) + penltyWeight * reward) * getShardTX(shardSet[i]) - penltyWeight * resCount(resourceSet.begin()->first, resourceSet.end()->first);

            Li = Li + getLamba(shardSet[i]) * (getShardTX(shardSet[i] - blockSize * blockInterval / slotsInterval));
        }

        L = f + LK + Li;

        if ((iter > 2) && (abs(f - L) < tol))
            break;

        return 0;
    }
}



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