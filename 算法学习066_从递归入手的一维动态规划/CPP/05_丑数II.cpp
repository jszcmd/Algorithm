// 丑数 II
// 给你一个整数 n ,请你找出并返回第 n 个 丑数
// 丑数 就是只包含质因数 2、3 或 5 的正整数
// 测试链接 : https://leetcode.cn/problems/ugly-number-ii/

#include <vector>
#include <algorithm>
using std::vector;
using std::min;

class Solution
{
public:
    int nthUglyNumber(int n)
    {
        vector<int> dp(n + 1, 0);
        dp[1] = 1;
        for (int i = 2, i2 = 1, i3 = 1, i5 = 1, a, b, c, cur; i <= n; ++i)
        {
            // i2表示乘以2的指针*哪一个下标的数字。
            // i3表示乘以3的指针*哪一个下标的数字。
            // i5表示乘以5的指针*哪一个下标的数字。
            a = dp[i2] * 2;
            b = dp[i3] * 3;
            c = dp[i5] * 5;
            cur = min(min(a, b), c);
            if (cur == a)
            {
                i2++;
            }
            if (cur == b)
            {
                i3++;
            }
            if (cur == c)
            {
                i5++;
            }
            dp[i] = cur;
        }
        return dp[n];
    }
};
