// 交错字符串
// 给定三个字符串 s1、s2、s3
// 请帮忙验证s3是否由s1和s2交错组成
// 测试链接 : https://leetcode.cn/problems/interleaving-string/

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:
    bool isInterleave(const string& s1, const string& s2, const string& s3)
    {
        return f1(s1, s2, s3);
    }

private:
    // dp[i][j]: s1[前缀长度为i]和s2[前缀长度为j]，能否交错组成出s3[前缀长度为i+j]
    // s1取前i个长度的字符,s2取前j个长度的字符 --> 能否交错出s3的前i+j长度的字符。
    // dp[n][m] --> s3[n+m] ? 
    // s3[i+j-1]最后一个字符来自哪?
    // (1): s1[i-1] == s3[i+j-1] 则s1[前i-1个字符]+s2[前j个字符]交错搞定s3[i+j-1个字符] dp[i-1][j]
    // (2): s2[j-1] == s3[i+j-1] 则s1[前i个字符]+s2[前j-1个字符]交错搞定s3[i+j-1个字符] dp[i][j-1]
    
    // 严格位置依赖的动态规划。
    bool f1(const string& s1, const string& s2, const string& s3)
    {
        if (s1.length() + s2.length() != s3.length())
        {
            return false;
        }
        int n = s1.length();
        int m = s2.length();
        vector<vector<bool>> dp(n + 1, vector<bool>(m + 1, false));
        dp[0][0] = true;
        // 搞定第0列。
        for (int i = 1; i <= n; ++i)
        {
            if (s1[i - 1] != s3[i - 1])
            {
                break;
            }
            dp[i][0] = true;
        }
        // 搞定第0行
        for (int j = 1; j <= m; ++j)
        {
            if (s2[j - 1] != s3[j - 1])
            {
                break;
            }
            dp[0][j] = true;
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                dp[i][j] = ((s1[i - 1] == s3[i + j - 1]) && dp[i - 1][j])
                    || ((s2[j - 1] == s3[i + j - 1]) && dp[i][j - 1]);
            }
        }
        return dp[n][m];
    }

    // 空间压缩。
    bool f2(const string& s1, const string& s2, const string& s3)
    {
        if (s1.length() + s2.length() != s3.length())
        {
            return false;
        }
        int n = s1.length();
        int m = s2.length();
        vector<bool> dp(m + 1, false);
        dp[0] = true;
        // 先处理第0行。
        for (int j = 1; j <= m; ++j)
        {
            if (s2[j - 1] != s3[j - 1])
            {
                break;
            }
            dp[j] = true;
        }
        for (int i = 1; i <= n; ++i)
        {
            dp[0] = (s1[i - 1] == s3[i - 1] && dp[0]);
            for (int j = 1; j <= m; ++j)
            {
                dp[j] = (s1[i - 1] == s3[i + j - 1] && dp[j])
                    || (s2[j - 1] == s3[i + j - 1] && dp[j - 1]);
            }
        }
        return dp[m];
    }
};