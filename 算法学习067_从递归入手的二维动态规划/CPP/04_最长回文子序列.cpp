// 2026年09月27日。

// 最长回文子序列
// 给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度
// 测试链接 : https://leetcode.cn/problems/longest-palindromic-subsequence/

#include <vector>
#include <string>
#include <algorithm>
using std::string;
using std::vector;
using std::max;

class Solution
{
public:
    int longestPalindromeSubseq(string s)
    {
        //return ans1(s);
        return f3(s);
    }

private:

    int ans1(const string& s)
    {
        string s1 = s;
        string s2 = s;
        reverse(s2.begin(), s2.end()); // 反转字符串。
        return longestCommonSubsequence(s1, s2);
    }

    // 空间压缩。
    int longestCommonSubsequence(string& s1, string& s2)
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

    // 暴力递归。
    int f1(const string& s)
    {
        return _f1(s, 0, s.length());
    }
    // s[l...r]最长回文子序列长度 l <= r
    int _f1(const string& s, int l, int r)
    {
        if (l == r)
        {
            return 1;
        }
        if (l + 1 == r)
        {
            return s[l] == s[r] ? 2 : 1;
        }
        if (s[l] == s[r])
        {
            return 2 + _f1(s, l + 1, r - 1);
        }
        else
        {
            return max(_f1(s, l + 1, r), _f1(s, l, r - 1));
        }
    }

    // 严格位置依赖的动态规划。
    int f2(const string& s)
    {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for (int l = n - 1; l >= 0; --l)
        {
            dp[l][l] = 1;
            if (l + 1 < n)
            {
                dp[l][l + 1] = (s[l] == s[l + 1]) ? 2 : 1;
            }
            for (int r = l + 2; r < n; ++r)
            {
                if (s[l] == s[r])
                {
                    dp[l][r] = 2 + dp[l + 1][r - 1];
                }
                else
                {
                    dp[l][r] = max(dp[l + 1][r], dp[l][r - 1]);
                }
            }
        }
        return dp[0][n - 1];
    }

    // 空间压缩。
    int f3(const string& s)
    {
        int n = s.length();
        vector<int> dp(n, 0);
        for (int l = n - 1, leftdown = 0, backup = 0; l >= 0; --l)
        {
            dp[l] = 1;
            if (l + 1 < n)
            {
                leftdown = dp[l + 1];
                dp[l + 1] = (s[l] == s[l + 1]) ? 2 : 1;
            }
            for (int r = l + 2; r < n; ++r)
            {
                backup = dp[r];
                if (s[l] == s[r])
                {
                    dp[r] = 2 + leftdown;
                }
                else
                {
                    dp[r] = max(dp[r], dp[r - 1]);
                }
                leftdown = backup;
            }
        }
        return dp[n - 1];
    }
};