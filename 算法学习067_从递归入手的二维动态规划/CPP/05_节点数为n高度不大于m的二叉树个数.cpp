// 节点数为n高度不大于m的二叉树个数
// 现在有n个节点，计算出有多少个不同结构的二叉树
// 满足节点个数为n且树的高度不超过m的方案
// 因为答案很大，所以答案需要模上1000000007后输出
// 测试链接 : https://www.nowcoder.com/practice/aaefe5896cce4204b276e213e725f3ea

#include <iostream>
#include <vector>
using std::vector;
using std::cin;
using std::cout;
using std::endl;

class Solution
{

public:
    Solution() : _mod(1000000007) {};
    int get_ans(int n, int m) { return compute1(n, m); };

private:

    int _mod = 1000000007;

    // 二叉树的节点为n,高度不能超过m;
    // 一个有多少种结构,返回。
    int compute1(int n, int m)
    {
        vector<vector<long long>> v(n + 1, vector<long long>(m + 1, -1));
        return _compute1(n, m, v);
    }
    // 挂一个傻的缓存表。 --> 递归形式。
    int _compute1(int n, int m, vector<vector<long long>>& dp)
    {
        if (n == 0) // 节点数为0;只有一种结构:空树。
        {
            return 1;
        }
        if (m == 0) // 节点数大于0 && 高度不能超过0
        {
            return 0; // 不可能。
        }
        if (dp[n][m] != -1)
        {
            return (int)dp[n][m];
        }
        long long ans = 0;
        // k枚举左树的大小,最大是n-1(因为头节点需要占用一个)
        for (int k = 0; k < n; ++k)
        {
            // 使用 (long long)的乘法,防止溢出。
            ans = (ans + (long long)_compute1(k, m - 1, dp) * _compute1(n - 1 - k, m - 1, dp) % _mod) % _mod;
            //ans = (ans + (long long)((_compute1(k, m - 1, dp) * _compute1(n - 1 - k, m - 1, dp)) % _mod)) % _mod;
        }
        dp[n][m] = ans;
        return (int)ans;
    }

    // 严格位置依赖的动态规划。
    int compute2(int n, int m)
    {
        if (n == 0) // 节点数为0;只有一种结构:空树。
        {
            return 1;
        }
        if (m == 0) // 节点数大于0 && 高度不能超过0
        {
            return 0; // 不可能。
        }
        vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, 0));
        for (int i = 0; i <= m; ++i) // 第0行的所有的情况都都是1
        {
            dp[0][i] = 1;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = 0;
                for (int k = 0; k < i; ++k)
                {
                    dp[i][j] = ((dp[i][j] + ((dp[k][j - 1] * dp[i - 1 - k][j - 1]) % _mod)) % _mod);
                }
            }
        }
        return (int)dp[n][m];
    }

    // 空间压缩。
    int compute3(int n, int m)
    {
        if (n == 0) // 节点数为0;只有一种结构:空树。
        {
            return 1;
        }
        if (m == 0) // 节点数大于0 && 高度不能超过0
        {
            return 0; // 不可能。
        }
        vector<vector<long long>> dp(n + 1, vector<long long>(1, 0)); // 创建一个列向量。
        // 从下往上更新。
        dp[0][0] = 1; // 0列0行的值。
        for (int j = 1; j <= m; ++j) // 执行m次。推出第几列的
        {
            for (int i = n; i > 0; --i) // 往上推,不同填写0的时候,因为是0
            {
                dp[i][0] = 0; // 现在代表的就是第i行,第j列的。
                for (int k = 0; k < i; ++k)
                {
                    // dp[0][k] * dp[0][n - k - 1] 天然就代表j-1列的数据。 
                    dp[i][0] = ((dp[i][0] + ((dp[k][0] * dp[i - 1 - k][0]) % _mod)) % _mod);
                }
            }
        }
        return (int)dp[n][0];
    }
};

int main()
{
    Solution s = Solution();
    int a, b;
    while (cin >> a >> b) // 注意 while 处理多个 case
    { 
        cout << s.get_ans(a, b) << endl;
    }
    return 0;
}
