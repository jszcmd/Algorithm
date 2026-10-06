// 一和零(多维费用背包)
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n
// 请你找出并返回 strs 的最大子集的长度
// 该子集中 最多 有 m 个 0 和 n 个 1 ==> 二维费用背包问题。
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
// 测试链接 : https://leetcode.cn/problems/ones-and-zeroes/


#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::max;

class Solution
{
public:
    int findMaxForm(const vector<string>& strs, int m, int n)
    {
        return f2(strs, m, n);
    }

private:
    int _zeros = 0;
    int _ones = 0;

    // 统计一个字符串中 '0'和'1'的数量。
    void _count(const string& str)
    {
        _zeros = 0;
        _ones = 0;
        for (auto e : str)
        {
            if (e == '0')
            {
                _zeros++;
            }
            else
            {
                _ones++;
            }
        }
    }

    // 暴力递归的版本。
    int f1(const vector<string>& strs, int m, int n)
    {
        return _f1(strs, 0, m, n);
    }
    // strs[i...]自由选择,希望0的数量不超过z,1的数量不超过o
    // 能最多选多少个字符串。
    int _f1(const vector<string>& strs, int i, int z, int o)
    {
        if (i == strs.size()) // 没有字符串了。
        {
            return 0;
        }
        // 不使用当前str[i]位置的字符串。
        int p1 = _f1(strs, i + 1, z, o);
        // 使用当前strs[i]位置的字符串
        int p2 = 0;
        _count(strs[i]);
        if (_zeros <= z && _ones <= o) // 需要保证当前的字符串不能超过额度。
        {
            p2 = 1 + _f1(strs, i + 1, z - _zeros, o - _ones);
        }
        return max(p1, p2);
    }

    // 挂一个傻傻的缓存表。
    int f2(const vector<string>& strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> v(len, vector<vector<int>>(m + 1, vector<int>(n + 1, -1)));
        return _f2(strs, 0, m, n, v);
    }
    int _f2(const vector<string>& strs, int i, int z, int o, vector<vector<vector<int>>>& dp)
    {
        if (i == strs.size()) // 没有字符串了。
        {
            return 0;
        }
        if (dp[i][z][o] != -1)
        {
            return dp[i][z][o];
        }
        int p1 = _f2(strs, i + 1, z, o, dp);
        int p2 = 0;
        _count(strs[i]);
        if (_zeros <= z && _ones <= o) // 需要保证当前的字符串不能超过额度。
        {
            p2 = 1 + _f2(strs, i + 1, z - _zeros, o - _ones, dp); // 依赖上一层的格子。
        }
        int ans = max(p1, p2);
        dp[i][z][o] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划。
    int f3(const vector<string>& strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(m + 1, vector<int>(n + 1, 0)));
        // 最上面的一层都是0.
        for (int i = len - 1; i >= 0; --i)
        {
            _count(strs[i]); // 计算str[i]的字符串中的1和0的个数。
            for (int z = 0, p1 = 0, p2 = 0; z <= m; ++z)
            {
                for (int o = 0; o <= n; ++o)
                {
                    p1 = dp[i + 1][z][o];
                    p2 = 0;
                    if (_zeros <= z && _ones <= o) // 需要保证当前的字符串不能超过额度。
                    {
                        p2 = 1 + dp[i + 1][z - _zeros][o - _ones];
                    }
                    dp[i][z][o] = max(p1, p2);
                }
            }
        }
        return dp[0][m][n];
    }

    // 空间压缩的动态规划。
    int f4(const vector<string>& strs, int m, int n)
    {
        int len = strs.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
        // 最上面的一层都是0.
        for (auto& str : strs) // 每一次来一个字符串更新一遍这一张表。
        {
            _count(str);
            for (int z = m; z >= _zeros; --z)
            {
                for (int o = n; o >= _ones; --o)
                {
                    dp[z][o] = max(dp[z][o], 1 + dp[z - _zeros][o - _ones]);
                }
                // dp[z][o](下) = dp[z][o](上) --> 不需要更新了,天然就是了。
            }
        }
        return dp[m][n];
    }
};