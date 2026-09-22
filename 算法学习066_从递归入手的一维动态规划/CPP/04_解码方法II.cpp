// 解码方法 II
// 由于答案数目可能非常大，答案对 1000000007 取模
// 测试链接 : https://leetcode.cn/problems/decode-ways-ii/

// 2026年09年21日。

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:

#define MOD 1000000007 // 取模。

    int numDecodings(string s)
    {
        return f4(s);
    }

private:

    int f1(const string& s)
    {
        return _f1(s, 0);
    }
    // s[i...有多少种有效的转化。
    int _f1(const string& s, int i)
    {
        if (s.length() == i)
        {
            return 1;
        }
        if (s[i] == '0')
        {
            return 0;
        }
        // s[i]位置的字符一定不是0
        int ans = _f1(s, i + 1) * (s[i] == '*' ? 9 : 1);
        // i 和 i+1 位置一起转化。
        if (i + 1 < s.length())
        {
            if (s[i] != '*')
            {
                if (s[i + 1] != '*') // i也不是*,i+1不是*。
                {
                    if (((s[i] - '0') * 10 + (s[i + 1] - '0')) <= 26)
                    {
                        ans += _f1(s, i + 2);
                    }
                }
                else // i不是*,i+1不是*。
                {
                    if (s[i] == '1')
                    {
                        ans += _f1(s, i + 2) * 9;
                    }
                    if (s[i] == '2')
                    {
                        ans += _f1(s, i + 2) * 6;
                    }
                }
            }
            else
            {
                if (s[i + 1] != '*') // i位置的字符是*,i+1位置的字符不是*
                {
                    if (s[i + 1] <= '6') // 以i+1是1为例子。11 21
                    {
                        ans += _f1(s, i + 2) * 2;
                    }
                    else // i只能变成1
                    {
                        ans += _f1(s, i + 2);
                    }
                }
                else // * *
                {
                    // 11 12 ... 19 ; 21 22 ... 26
                    ans += _f1(s, i + 2) * 15;
                }
            }
        }
        return ans;
    }

    // 挂缓存表。
    int f2(const string& s)
    {
        // return _f1(s, 0);
        int n = s.length();
        vector<long long> v(n, -1);
        return (int)_f2(s, 0, v);
    }
    long long _f2(const string& s, int i, vector<long long>& dp)
    {
        if (s.length() == i)
        {
            return 1;
        }
        if (s[i] == '0')
        {
            return 0;
        }
        if (dp[i] != -1)
        {
            return dp[i];
        }
        // s[i]位置的字符一定不是0
        long long ans = _f2(s, i + 1, dp) * (s[i] == '*' ? 9 : 1);
        // i 和 i+1 位置一起转化。
        if (i + 1 < s.length())
        {
            if (s[i] != '*')
            {
                if (s[i + 1] != '*') // i也不是*,i+1不是*。
                {
                    if (((s[i] - '0') * 10 + (s[i + 1] - '0')) <= 26)
                    {
                        ans += _f2(s, i + 2, dp);
                    }
                }
                else // i不是*,i+1不是*。
                {
                    if (s[i] == '1')
                    {
                        ans += _f2(s, i + 2, dp) * 9;
                    }
                    if (s[i] == '2')
                    {
                        ans += _f2(s, i + 2, dp) * 6;
                    }
                }
            }
            else
            {
                if (s[i + 1] != '*') // i位置的字符是*,i+1位置的字符不是*
                {
                    if (s[i + 1] <= '6') // 以i+1是1为例子。11 21
                    {
                        ans += _f2(s, i + 2, dp) * 2;
                    }
                    else // i只能变成1
                    {
                        ans += _f2(s, i + 2, dp);
                    }
                }
                else // * *
                {
                    // 11 12 ... 19 ; 21 22 ... 26
                    ans += _f2(s, i + 2, dp) * 15;
                }
            }
        }
        ans %= MOD;
        dp[i] = ans;
        return ans;
    }

    // 严格位置依赖的从底到顶的动态规划。
    int f3(const string& s)
    {
        int n = s.length();
        vector<long long > dp(n + 1, 0);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            if (s[i] != '0')
            {
                // s[i]位置的字符一定不是0
                //long long ans = _f2(s, i + 1, dp) * (s[i] == '*' ? 9 : 1);
                dp[i] = (s[i] == '*' ? 9 : 1) * dp[i + 1];
                // i 和 i+1 位置一起转化。
                if (i + 1 < s.length())
                {
                    if (s[i] != '*')
                    {
                        if (s[i + 1] != '*') // i也不是*,i+1不是*。
                        {
                            if (((s[i] - '0') * 10 + (s[i + 1] - '0')) <= 26)
                            {
                                dp[i] += dp[i + 2];
                                //ans += _f2(s, i + 2, dp);
                            }
                        }
                        else // i不是*,i+1不是*。
                        {
                            if (s[i] == '1')
                            {
                                dp[i] += dp[i + 2] * 9;
                                //ans += _f2(s, i + 2, dp) * 9;
                            }
                            if (s[i] == '2')
                            {
                                dp[i] += dp[i + 2] * 6;
                                //ans += _f2(s, i + 2, dp) * 6;
                            }
                        }
                    }
                    else
                    {
                        if (s[i + 1] != '*') // i位置的字符是*,i+1位置的字符不是*
                        {
                            if (s[i + 1] <= '6') // 以i+1是1为例子。11 21
                            {
                                dp[i] += dp[i + 2] * 2;
                                //ans += _f2(s, i + 2, dp) * 2;
                            }
                            else // i只能变成1
                            {
                                dp[i] += dp[i + 2];
                                //ans += _f2(s, i + 2, dp);
                            }
                        }
                        else // * *
                        {
                            // 11 12 ... 19 ; 21 22 ... 26
                            dp[i] += dp[i + 2] * 15;
                            //ans += _f2(s, i + 2, dp) * 15;
                        }
                    }
                }
            }
            dp[i] %= MOD;
        }
        return (int)dp[0];
    }

    // 有限个变量滚动。
    int f4(const string& s)
    {
        int n = s.length();
        long long cur = 0, next = 1, next_next = 0;
        for (int i = n - 1; i >= 0; --i)
        {
            if (s[i] != '0')
            {
                cur = (s[i] == '*' ? 9 : 1) * next;
                // i 和 i+1 位置一起转化。
                if (i + 1 < s.length())
                {
                    if (s[i] != '*')
                    {
                        if (s[i + 1] != '*') // i也不是*,i+1不是*。
                        {
                            if (((s[i] - '0') * 10 + (s[i + 1] - '0')) <= 26)
                            {
                                cur += next_next;
                            }
                        }
                        else // i不是*,i+1不是*。
                        {
                            if (s[i] == '1')
                            {
                                cur += next_next * 9;
                            }
                            if (s[i] == '2')
                            {
                                cur += next_next * 6;
                            }
                        }
                    }
                    else
                    {
                        if (s[i + 1] != '*') // i位置的字符是*,i+1位置的字符不是*
                        {
                            if (s[i + 1] <= '6') // 以i+1是1为例子。11 21
                            {
                                cur += next_next * 2;
                            }
                            else // i只能变成1
                            {
                                cur += next_next;
                            }
                        }
                        else // * *
                        {
                            cur += next_next * 15;
                        }
                    }
                }
                cur %= MOD;
            }
            next_next = next;
            next = cur;
            cur = 0;
        }
        return (int)next;
    }
};
