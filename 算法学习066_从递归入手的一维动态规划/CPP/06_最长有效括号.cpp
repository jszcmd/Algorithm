// 最长有效括号
// 给你一个只包含 '(' 和 ')' 的字符串
// 找出最长有效(格式正确且连续)括号子串的长度。
// 测试链接 : https://leetcode.cn/problems/longest-valid-parentheses/

#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::max;

class Solution
{
public:
    int longestValidParentheses(const string& s)
    {
        int n = s.length();
        // dp[0...n-1]
        // dp[i] : 子串必须以i位置的字符结尾的情况下,往左整体有效的最大长度
        vector<int> dp(n, 0); 
        // dp[0] = 0;
        int ans = 0;
        for (int i = 1, p; i < n; ++i)
        {
            if (s[i] == ')')
            {
                p = i - 1 - dp[i - 1];
                if ((p >= 0) && (s[p] == '('))
                {
                    dp[i] = dp[i - 1] + 2 + ((p - 1 >= 0) ? dp[p - 1] : 0);
                }
            }
            ans = max(ans, dp[i]);
        }
        return ans;
    }
};