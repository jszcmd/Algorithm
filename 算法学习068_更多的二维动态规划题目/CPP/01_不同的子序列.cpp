// 2026年10月01日 --> 国庆节快乐。

// 不同的子序列
// 给你两个字符串s和t ，统计并返回在s的子序列中t出现的个数
// 答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences/

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:
    Solution() :_mod(1000000007) {};

    int numDistinct(const string& s, const string& t)
    {
        return f1(s, t);
    }
private:

    int _mod = 1000000007;
    // 严格位置依赖的动态规划。
    int f1(const string& s, const string& t)
    {
        int n = s.length();
        int m = t.length();
        // dp[i][j] : s[前缀长度为i]的所有子序列中,有多少个子序列等于t[前缀长度为j]
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i <= n; ++i) // 第0列初始化成1
        {
            dp[i][0] = 1;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                // (1) : 不要s[i - 1]位置的字符。s[前缀长度为i - 1]的所有子序列中, 有多少个子序列等于t[前缀长度为j]
                dp[i][j] = dp[i - 1][j] % _mod;
                if (s[i - 1] == t[j - 1]) // (2):要s[i-1]位置的字符。 s[i-1]需要和t[i-1]的字符需要对上。
                {
                    dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % _mod;
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩。
    int f2(const string& s, const string& t)
    {
        int n = s.length();
        int m = t.length();
        vector<int> dp(m + 1, 0);
        dp[0] = 1; // 第0行的格子是1。
        for (int i = 1; i <= n; ++i)
        {
            for (int j = m; j >= 1; --j)
            {
                //dp[i][j] = dp[i - 1][j];
                // dp[j] = dp[j] // 自己没有更新之前就是上一行的。
                if (s[i - 1] == t[j - 1])
                {
                    dp[j] = (dp[j] + dp[j - 1]) % _mod;
                }
            }
        }
        return dp[m];
    }
};