// 最小路径和
// 给定一个包含非负整数的 m x n 网格 grid
// 请找出一条从左上角到右下角的路径, 使得路径上的数字总和为最小.
// 说明: 每次只能向下或者向右移动一步.
// 测试链接 : https://leetcode.cn/problems/minimum-path-sum/

// 2026年09月23日。

#include <vector>
#include <climits>
#include <algorithm>
using std::vector;
using std::min;

class Solution
{
public:
    int minPathSum(const vector<vector<int>>& grid)
    {
        return f4(grid);
    }

private:
    // 暴力递归的过程。
    int f1(const vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        return _f1(grid, m - 1, n - 1);
    }
    // 从(0,0)点到(i,j)点,最小路径和,每一次一定只能像右边或者像下边。
    int _f1(const vector<vector<int>>& grid, int i, int j)
    {
        if (i == 0 && j == 0)
        {
            return grid[0][0];
        }
        int up = INT_MAX;
        int left = INT_MAX;
        if (i - 1 >= 0)
        {
            up = _f1(grid, i - 1, j);
        }
        if (j - 1 >= 0)
        {
            left = _f1(grid, i, j - 1);
        }
        return grid[i][j] + min(up, left);
    }

    // 记忆化搜索。
    int f2(const vector<vector<int>>& grid)
    {
        int m = grid.size(); // 行数。
        int n = grid[0].size(); // 列数。
        // m行n列的缓存表,全部初始化成-1。
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return _f2(grid, m - 1, n - 1, dp);
    }
    // 从(0,0)点到(i,j)点,最小路径和,每一次一定只能像右边或者像下边。
    int _f2(const vector<vector<int>>& grid, int i, int j, vector<vector<int>>& dp)
    {
        if (dp[i][j] != -1)
        {
            return dp[i][j];
        }
        int ans = 0;
        if (i == 0 && j == 0)
        {
            ans = grid[0][0];
        }
        else
        {
            int up = INT_MAX;
            int left = INT_MAX;
            if (i - 1 >= 0)
            {
                up = _f2(grid, i - 1, j, dp);
            }
            if (j - 1 >= 0)
            {
                left = _f2(grid, i, j - 1, dp);
            }
            ans = grid[i][j] + min(up, left);
        }
        dp[i][j] = ans;
        return ans;
    }

    // 严格位置依赖的动态规划。
    int f3(const vector<vector<int>>& grid)
    {
        int m = grid.size(); // 行数。
        int n = grid[0].size(); // 列数。
        vector<vector<int>> dp(m, vector<int>(n, -1));
        dp[0][0] = grid[0][0];
        for (int i = 1; i < m; ++i)
        {
            dp[i][0] = dp[i - 1][0] + grid[i][0];
        }
        for (int i = 1; i < n; ++i)
        {
            dp[0][i] = dp[0][i - 1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j < n; ++j)
            {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + grid[i][j];
            }
        }
        return dp[m - 1][n - 1];
    }

    // 空间压缩。
    int f4(const vector<vector<int>>& grid)
    {
        int m = grid.size(); // 行数。
        int n = grid[0].size(); // 列数。
        vector<int> dp(n, 0);
        dp[0] = grid[0][0];
        for (int i = 1; i < n; ++i)
        {
            dp[i] = dp[i - 1] + grid[0][i];
        }
        for (int i = 1; i < m; ++i)
        {
            dp[0] += grid[i][0];
            for (int j = 1; j < n; ++j)
            {
                dp[j] = min(dp[j - 1], dp[j]) + grid[i][j];
            }
        }
        return dp[n - 1];
    }
};