// 解码方法
// 测试链接 : https://leetcode.cn/problems/decode-ways/

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:
    int numDecodings(string s)
    {
        //return f1(s, 0);
        return f2(s);
    }

private:

    // 从s[i...位置开始,有多少种有效的转化方式。
    int f1(const string& s, int i)
    {
        if (i == s.length())
        {
            return 1; // 之前做的决策连起来是一种有效的转化。
        }
        int ans = 0;
        if (s[i] == '0')
        {
            return 0;
        }
        else // s[i]一定不是0
        {
            ans = f1(s, i + 1); // s[i]单独转
            if ((i + 1 < s.length()) && ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
            {
                ans += f1(s, i + 2);
            }
        }
        return ans;
    }

    // 挂缓存表。
    int f2(const string& s)
    {
        vector<int> dp(s.length(), -1);
        return _f2(s, 0, dp);
    }
    int _f2(const string& s, int i, vector<int>& dp)
    {
        if (i == s.length())
        {
            return 1;
        }
        if (dp[i] != -1)
        {
            return dp[i];
        }
        int ans = 0;
        if (s[i] == '0')
        {
            dp[i] = 0;
            return 0;
        }
        else // s[i]一定不是0
        {
            ans = _f2(s, i + 1,dp); // s[i]单独转
            if ((i + 1 < s.length()) && ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
            {
                ans += _f2(s, i + 2, dp);
            }
        }
        dp[i] = ans;
        return ans;
    }

    // 从底到顶的动态规划。
    int f3(const string& s)
    {
        int n = s.length();
        vector<int> dp(n + 1, -1);
        dp[n] = 1;
        for (int i = n - 1; i >= 0; --i)
        {
            if (s[i] == '0')
            {
                dp[i] = 0;
            }
            else // s[i]一定不是0
            {
                dp[i] = dp[i + 1];
                if ((i + 1 < s.length()) && ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
                {
                    dp[i] += dp[i + 2];
                }
            }
        }
        return dp[0];
    }

    // 有限个变量滚动。
    int f4(const string& s)
    {
        int next = 1; // dp[n] --> dp[i+1]
        int next_next = 0; // dp[n+1] 不存在。 dp[i+2]
        for (int i = s.length() - 1, cur; i >= 0; --i)
        {
            if (s[i] == '0')
            {
                cur = 0;
            }
            else // s[i]一定不是0
            {
                cur = next;
                //dp[i] = dp[i + 1];
                if ((i + 1 < s.length()) && ((s[i] - '0') * 10 + (s[i + 1] - '0') <= 26))
                {
                    cur += next_next;
                    //dp[i] += dp[i + 2];
                }
            }
            next_next = next;
            next = cur;
        }
        return next;
    }

};