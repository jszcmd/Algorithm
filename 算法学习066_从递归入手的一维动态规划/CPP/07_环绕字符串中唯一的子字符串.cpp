// 环绕字符串中唯一的子字符串
// 定义字符串 base 为一个 "abcdefghijklmnopqrstuvwxyz" 无限环绕的字符串
// 所以 base 看起来是这样的：
// "..zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd.."
// 给你一个字符串 s ，请你统计并返回 s 中有多少 不同非空子串 也在 base 中出现
// 测试链接 : https://leetcode.cn/problems/unique-substrings-in-wraparound-string/

#include <string>
#include <vector>
#include <algorithm>
using std::string;
using std::vector;
using std::max;

class Solution
{
public:
    int findSubstringInWraproundString(const string& str)
    {
        int n = str.length();
        vector<int> s(n, 0);
        for (int i = 0; i < n; ++i)
        {
            s[i] = str[i] - 'a';
        }
        // dp[0]代表在s串中必须以'a'结尾的字串最大的延伸长度是多少。
        vector<int> dp(26, 0);
        dp[s[0]] = 1;
        for (int i = 1, cur, pre, len = 1; i < n; ++i)
        {
            cur = s[i]; // 当前的字符,已经转化成数字了。
            pre = s[i - 1]; // 左边的字符,已经转化成数字了.
            // pre cur 
            // (前一个字符是'z' && 当前字符是'a') || 前一个字符比当前字符的ascii码少1
            if ((pre == 25 && cur == 0) || (pre + 1 == cur))
            {
                len++;
            }
            else
            {
                len = 1; // 不能延伸
            }
            dp[cur] = max(dp[cur], len);
        }
        int ans = 0;
        for (int i = 0; i < 26; ++i)
        {
            ans += dp[i];
        }
        return ans;
    }
};