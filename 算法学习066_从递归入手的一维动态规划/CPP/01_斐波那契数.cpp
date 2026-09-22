// 斐波那契数
// 斐波那契数 (通常用 F(n) 表示)形成的序列称为 斐波那契数列
// 该数列由 0 和 1 开始,后面的每一项数字都是前面两项数字的和。
// 也就是：F(0) = 0，F(1) = 1
// F(n) = F(n - 1) + F(n - 2)，其中 n > 1
// 给定 n ,请计算 F(n)
// 测试链接 : https://leetcode.cn/problems/fibonacci-number/

#include <cstring>

class Solution
{
public:
    int fib(int n)
    {
        return fib1(n);
    }
private:
    // 时间复杂度 O(2^n)
    int fib1(int n) // 暴力递归。
    {
        if (n == 0)
        {
            return 0;
        }
        if ((n == 1) || (n == 2))
        {
            return 1;
        }
        return fib1(n - 1) + fib1(n - 2);
    }

    // 从顶到底的动态规划。
    // 时间复杂度: O(n) 
    int fib2(int n)
    {
        int* dp = new int[n + 1];
        memset(dp, 0xFF, sizeof(int) * (n + 1)); // 全部初始化成为-1
        int ans = _fib2(n, dp);
        delete[] dp;
        return ans;
    }
    int _fib2(int i, int* dp)
    {
        if (i == 0)
        {
            return 0;
        }
        if ((i == 1) || (i == 2))
        {
            return 1;
        }
        if (dp[i] != -1)
        {
            return dp[i];
        }
        int ans = _fib2(i - 1, dp) + _fib2(i - 2, dp);
        dp[i] = ans;
        return dp[i];
    }

    // 从底到顶的动态规划。
    int fib3(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        if ((n == 1) || (n == 2))
        {
            return 1;
        }
        int* dp = new int[n + 1];
        memset(dp, 0, (n + 1) * sizeof(int)); // 全部初始化成0
        dp[1] = 1; 
        for (int i = 2; i <= n; ++i)
        {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        int ans = dp[n];
        delete[] dp;
        return ans;
    }

    // 有限的几个变量。滚动更新。
    int fib4(int n)
    {
        if (n == 0)
        {
            return 0;
        }
        if (n == 1)
        {
            return 1;
        }
        int last_last = 0, last = 1;
        for (int i = 2, cur; i <= n; ++i)
        {
            cur = last_last + last;
            last_last = last;
            last = cur;
        }
        return last;
    }
};
