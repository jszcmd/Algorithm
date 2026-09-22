// 测试链接 : https://leetcode.cn/problems/minimum-cost-for-tickets/

#include <vector>
#include <climits>   // 提供 INT_MAX
using std::vector;
using std::min;

class Solution
{
public:
    int mincostTickets(vector<int>& days, vector<int>& costs)
    {
        return _f1(days, costs, 0);
        /*return f2(days, costs);
        return f3(days, costs);*/
    }

private:
    vector<int> _durations = { 1, 7, 30 };

    // days[i...]从下标i开始,搞定后面的所有的旅行的最小花费。
    int _f1(vector<int>& days, vector<int>& costs, int i)
    {
        if (i == days.size()) // 后续已经无旅行了。
        {
            return 0;
        }
        int ans = INT_MAX; // 从days[i]开始的最少的花费是多少。
        for (int k = 0, j = i; k < 3; ++k)
        {
            // k是方案的编号: 0 1 2
            while ((j < days.size()) && (days[i] + _durations[k] > days[j]))
            {
                j++;
            }
            ans = min(ans, costs[k] + _f1(days, costs, j));
        }
        return ans;
    }

    // 从顶到底的动态规划。
    int f2(vector<int>& days, vector<int>& costs)
    {
        int n = days.size();
        vector<int> dp(n, INT_MAX); 
        return _f2(days, costs, 0, dp);
    }
    // 记忆化搜索。
    int _f2(vector<int>& days, vector<int>& costs, int i, vector<int>& dp)
    {
        if (i == days.size()) // 后续已经无旅行了。
        {
            return 0;
        }
        if (dp[i] != INT_MAX)
        {
            return dp[i];
        }
        int ans = INT_MAX; // 从days[i]开始的最少的花费是多少。
        for (int k = 0, j = i; k < 3; ++k)
        {
            // k是方案的编号: 0 1 2
            while ((j < days.size()) && (days[i] + _durations[k] > days[j]))
            {
                j++;
            }
            ans = min(ans, costs[k] + _f2(days, costs, j, dp));
        }
        dp[i] = ans;
        return ans;
    }

    // 从底到顶的动态规划。
    int f3(vector<int>& days, vector<int>& costs)
    {
        int MAXN = 366;
        vector<int> dp(MAXN, INT_MAX);
        int n = days.size();
        dp[n] = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            for (int k = 0, j = i; k < 3; ++k)
            {
                // k是方案的编号: 0 1 2
                while ((j < days.size()) && (days[i] + _durations[k] > days[j]))
                {
                    j++;
                }
                dp[i] = min(dp[i], costs[k] + dp[j]);
            }
        }
        return dp[0];
    }
};
