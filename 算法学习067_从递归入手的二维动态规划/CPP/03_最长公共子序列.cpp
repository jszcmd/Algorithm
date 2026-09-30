// 2026年09月26日。
// 最长公共子序列
// 给定两个字符串text1和text2
// 返回这两个字符串的最长 公共子序列 的长度
// 如果不存在公共子序列，返回0
// 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列
// 测试链接 : https://leetcode.cn/problems/longest-common-subsequence/

// 子序列（subsequence）：原串中不要求连续、但保持相对顺序的一段。
// 子串（substring）：原串中连续的一段。

#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::max;

class Solution
{
public:
    int longestCommonSubsequence(string text1, string text2)
    {
        //return f2(text1, text2);
        //return f3(text1, text2);
        return f4(text1, text2);
    }

private:

    int f1(const string& s1, const string& s2)
    {
        int n = s1.length();
        int m = s2.length();
        //return _f1(s1, s2, n - 1, m - 1);
        return __f1__(s1, s2, n, m);
    }

    // s1[0...i1]这一段与s2[0...i2]这一段的最长的公共子序列。
    int _f1(const string& s1, const string& s2, int i1, int i2)
    {
        // 这里的i1和i2会出现到-1的情况,后续的动态规划表,就会比较麻烦。
        if (i1 < 0 || i2 < 0) // s1或者s2中没有子串了。
        {
            return 0;
        }
        int p1 = _f1(s1, s2, i1 - 1, i2 - 1);
        int p2 = _f1(s1, s2, i1 - 1, i2);
        int p3 = _f1(s1, s2, i1, i2 - 1);
        int p4 = (s1[i1] == s2[i2]) ? (p1 + 1) : 0;
        return max(max(p1, p2), max(p3, p4));
    }

    // s1[前缀长度为len1]对应s2[前缀长度为len2]这两个字符串的最长的公共子序列。
    int __f1__(const string& s1, const string& s2, int len1, int len2)
    {
        if (len1 == 0 || len2 == 0)
        {
            return 0;
        }
        int ans = 0;
        if (s1[len1 - 1] == s2[len2 - 1])
        {
            ans = __f1__(s1, s2, len1 - 1, len2 - 1) + 1;
        }
        else
        {
            ans = max(__f1__(s1, s2, len1, len2 - 1), __f1__(s1, s2, len1 - 1, len2));
        }
        return ans;
    }

    int f2(const string& s1, const string& s2)
    {
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        return _f2(s1, s2, n, m, dp);
    }

    int _f2(const string& s1, const string& s2, int len1, int len2, vector<vector<int>>& dp)
    {
        if (len1 == 0 || len2 == 0)
        {
            return 0;
        }
        if (dp[len1][len2] != -1)
        {
            return dp[len1][len2];
        }
        int ans = 0;
        if (s1[len1 - 1] == s2[len2 - 1])
        {
            ans = _f2(s1, s2, len1 - 1, len2 - 1, dp) + 1;
        }
        else
        {
            ans = max(_f2(s1, s2, len1, len2 - 1, dp), _f2(s1, s2, len1 - 1, len2, dp));
        }
        dp[len1][len2] = ans;
        return ans;
    }

    // 严格位置依赖。
    int f3(const string& s1, const string& s2)
    {
        int n = s1.length();
        int m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int len1 = 1; len1 <= n; ++len1)
        {
            for (int len2 = 1; len2 <= m; ++len2)
            {
                if (s1[len1 - 1] == s2[len2 - 1])
                {
                    dp[len1][len2] = dp[len1 - 1][len2 - 1] + 1;
                    //ans = _f2(s1, s2, len1 - 1, len2 - 1, dp) + 1;
                }
                else
                {
                    dp[len1][len2] = max(dp[len1][len2 - 1], dp[len1 - 1][len2]);
                    //ans = max(_f2(s1, s2, len1, len2 - 1, dp), _f2(s1, s2, len1 - 1, len2, dp));
                }
            }
        }
        return dp[n][m];
    }

    // 空间压缩。
    int f4(string& s1, string& s2)
    {
        if (s1.length() < s2.length())
        {
            s1.swap(s2);
        }
        int n = s1.length();
        int m = s2.length();
        vector<int> dp(m + 1, 0);
        for (int len1 = 1; len1 <= n; ++len1)
        {
            // leftup代表的是左上角的值。
            int leftup = 0, backup = 0;
            for (int len2 = 1; len2 <= m; ++len2)
            {
                backup = dp[len2]; // 它现在代表正上方角的值。
                if (s1[len1 - 1] == s2[len2 - 1])
                {
                    dp[len2] = 1 + leftup;
                }
                else
                {
                    //             dp[len2] 没有更新之前上方的值。
                    //             dp[len2 - 1] 没有更新之前的左边的值。
                    dp[len2] = max(dp[len2], dp[len2 - 1]);
                }
                leftup = backup; // 新左上角。
            }
        }
        return dp[m];
    }
};