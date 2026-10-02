// 编辑距离
// 给你两个单词 word1 和 word2
// 请返回将 word1 转换成 word2 所使用的最少代价
// 你可以对一个单词进行如下三种操作：
// 插入一个字符,代价a
// 删除一个字符,代价b
// 替换一个字符,代价c
// 测试链接 : https://leetcode.cn/problems/edit-distance/

#include <climits>
#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::min;

class Solution
{
public:
    int minDistance(string word1, string word2)
    {
        return minEditCost(word1, word2, 1, 1, 1);
    }

private:

    int minEditCost(const string& w1, const string& w2, int a, int b, int c)
    {
        return f1(w1, w2, a, b, c);
    }

    // dp[i][j] : s1[前缀长度为i]想变成s2[前缀长度为j]，至少付出多少代价
    // s1取出来前i个字符  // s2取出来前j个字符
    // s1[0...i-1]彻底变成[s2...j-1]个字符。
    // 
    // (大方案1): s1[i-1]位置的字符参与变换。
    //     a: s[i-1]位置的字符变成s2[j-1]
    //         (1):有可能s1[i-1] == s2[j-1] --> 就只需要考虑 s1[0...i-1]变成s2[0...j-1] --> dp[i-1][j-1]
    //         (2):当s1[i-1]!=s2[j-1]位置的字符 --> 需要加上一个替换的代价 dp[i-1][j-1] + 替换的代价。
    // 
    //     b: s1[i-1]参与,但是不是变成s2最后一个位置(j-1位置)的字符,可能搞定之前的字符串,最后插入s2[j-1]这个字符
    //         (3): s1[0...i-1] 搞定 s2[0...j-2]前i-1个字符。--> dp[i][j-2] + 一个插入的代价
    // 
    // (大方案2): s1[i-1]位置的字符不参与,把它删除掉。
    //         (4): s1[0...i-2] 前i-1个字符搞定 s2[0...i-1]这些字符 --> dp[i-1][j] + 一个删除的代价。

    // 严格位置依赖的动态规划。
    int f1(const string& s1, const string& s2, int a, int b, int c)
    {
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        // dp[0][0] = 0; 不需要代价。
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; ++j)
        {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                // (1) : 有可能s1[i - 1] == s2[j - 1] -- > 就只需要考虑 s1[0...i - 1]变成s2[0...j - 1] -- > dp[i - 1][j - 1]
                int p1 = INT_MAX;
                if (s1[i - 1] == s2[j - 1])
                {
                    p1 = dp[i - 1][j - 1];
                }
                // (2):当s1[i-1]!=s2[j-1]位置的字符 --> 需要加上一个替换的代价 dp[i-1][j-1] + 替换的代价。
                int p2 = INT_MAX;
                if (s1[i - 1] != s2[j - 1])
                {
                    p1 = dp[i - 1][j - 1] + c;
                }
                // (3): s1[0...i-1] 搞定 s2[0...j-2]前i-1个字符。--> dp[i][j-2] + 一个插入的代价
                int p3 = dp[i][j - 1] + a;
                // (4): s1[0...i-2] 前i-1个字符搞定 s2[0...i-1]这些字符 --> dp[i-1][j] + 一个删除的代价。
                int p4 = dp[i - 1][j] + b;
                dp[i][j] = min(min(p1, p2), min(p3, p4));
            }
        }
        return dp[n][m];
    }

    // 严格位置依赖的动态规划 // 枚举优化的版本。
    int f2(const string& s1, const string& s2, int a, int b, int c)
    {
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int i = 1; i <= n; ++i)
        {
            dp[i][0] = i * b;
        }
        for (int j = 1; j <= m; ++j)
        {
            dp[0][j] = j * a;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[i][j] = dp[i - 1][j - 1];
                }
                else
                {
                    dp[i][j] = min(dp[i - 1][j - 1] + c, min(dp[i][j - 1] + a, dp[i - 1][j] + b));
                }
            }
        }
        return dp[n][m];
    }

    // 严格位置依赖 + 空间压缩。
    int f3(const string& s1, const string& s2, int a, int b, int c)
    {
        int n = s1.length();
        int m = s2.length();
        vector<int> dp(m + 1, 0);
        for (int j = 1; j <= m; ++j)
        {
            dp[j] = j * a;
        }
        for (int i = 1, leftup, backup; i <= n; ++i)
        {
            leftup = (i - 1) * a; // 第一次进入的时候,左上角的位置。
            dp[0] = i * b;
            for (int j = 1; j <= m; j++)
            {
                backup = dp[j];
                if (s1[i - 1] == s2[j - 1])
                {
                    dp[j] = leftup;
                }
                else
                {
                    dp[j] = min(min(dp[j] + b, dp[j - 1] + a), leftup + c);
                }
                leftup = backup;
            }
        }
        return dp[m];
    }
};