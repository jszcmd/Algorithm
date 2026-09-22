// 不同的子序列 II
// 给定一个字符串 s，计算 s 的 不同非空子序列 的个数
// 因为结果可能很大，答案对 1000000007 取模
// 字符串的 子序列 是经由原字符串删除一些（也可能不删除）
// 字符但不改变剩余字符相对位置的一个新字符串
// 例如，"ace" 是 "abcde" 的一个子序列，但 "aec" 不是
// 测试链接 : https://leetcode.cn/problems/distinct-subsequences-ii/

#include <string>
#include <vector>
using std::string;
using std::vector;

class Solution
{
public:
    int distinctSubseqII(const string& s)
    {
        int mod = 1000000007; // 取模。
        vector<int> cnt(26, 0); 
        int all = 1, newAdd = 0;
        for (auto x : s)
        {
            newAdd = (all - cnt[x - 'a'] + mod) % mod;
            cnt[x - 'a'] = (cnt[x - 'a'] + newAdd) % mod;
            all = (all + newAdd) % mod;
        }
        return (all - 1 + mod) % mod;
    }
};