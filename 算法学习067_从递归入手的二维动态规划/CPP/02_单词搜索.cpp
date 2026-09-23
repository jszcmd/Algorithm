// 单词搜索(无法改成动态规划)
// 给定一个 m x n 二维字符网格 board 和一个字符串单词 word
// 如果 word 存在于网格中,返回 true ;否则,返回 false 。
// 单词必须按照字母顺序，通过相邻的单元格内的字母构成
// 其中"相邻"单元格是那些水平相邻或垂直相邻的单元格
// 同一个单元格内的字母不允许被重复使用
// 测试链接 : https://leetcode.cn/problems/word-search/

// 2026年09月23日。

#include <string>
#include <vector>
using std::vector;
using std::string;

class Solution
{
public:
    bool exist(vector<vector<char>>& board, string word)
    {
        for (int i = 0; i < board.size(); ++i)
        {
            for (int j = 0; j < board[0].size(); ++j)
            {
                if (_f(board, i, j, word, 0))
                {
                    return true;
                }
            }
        }
        return false;
    }

private:
    // 从(i,j)出发, 来到w[k],请问后续能不能把word走出来w[k...]
    bool _f(vector<vector<char>>& b, int i, int j, const string& w, int k)
    {
        if (k == w.length())
        {
            return true;
        }
        // i < 0 || i == b.size() || j < 0 || j == b[0].size()  越界了
        // b[i][j] != w[k] b[i][j] 不等于w[k]
        if (i < 0 || i == b.size() || j < 0 || j == b[0].size() || b[i][j] != w[k])
        {
            return false;
        }
        char tmp = b[i][j];
        b[i][j] = 0;
        bool ans = _f(b, i - 1, j, w, k + 1) // 往上走
            || _f(b, i + 1, j, w, k + 1) // 下
            || _f(b, i, j - 1, w, k + 1) // 左
            || _f(b, i, j + 1, w, k + 1); // 右
        b[i][j] = tmp;
        return ans;
    }
};