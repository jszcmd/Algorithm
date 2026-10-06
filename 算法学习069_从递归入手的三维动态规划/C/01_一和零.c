// 一和零(多维费用背包)
// 给你一个二进制字符串数组 strs 和两个整数 m 和 n
// 请你找出并返回 strs 的最大子集的长度
// 该子集中 最多 有 m 个 0 和 n 个 1 ==> 二维费用背包问题。
// 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集
// 测试链接 : https://leetcode.cn/problems/ones-and-zeroes/

#include <string.h>
#include <stdlib.h>

int _zeros = 0;
int _ones = 0;

inline int _max(int a, int b)
{
	return (a > b) ? a : b;
}

// 计算字符串str中的1和0的数量。
void _count(char* str)
{
	_zeros = 0;
	_ones = 0;
	int len = strlen(str);
	for (int i = 0; i < len; ++i)
	{
		if (str[i] == '0')
		{
			_zeros++;
		}
		else
		{
			_ones++;
		}
	}
}

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
// 暴力递归。

// sts[i...]往后的这些字符串自由选择,希望0不超过z,1不超过o的情况下
// --> 返回最多选择多少个字符串。
int _f1(char** strs, int strsSize, int i, int z, int o)
{
	if (i == strsSize) // 没有字符串。
	{
		return 0;
	}
	// 不使用当前str[i]位置的字符串。
	int p1 = _f1(strs, strsSize, i + 1, z, o); // 不选当前字符串。
	// 使用当前strs[i]位置的字符串
	_count(strs[i]);
	int p2 = 0;
	if (z >= _zeros && o >= _ones)
	{
		p2 = _f1(strs, strsSize, i + 1, z - _zeros, o - _ones) + 1;
	}
	return _max(p1, p2);
}

int f1(char** strs, int strsSize, int m, int n)
{
	return _f1(strs, strsSize, 0, m, n);
}

// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 挂一个傻傻的缓存表。

int _f2(char** strs, int strsSize, int i, int z, int o, int*** dp)
{
	if (i == strsSize) // 没有字符串。
	{
		return 0;
	}
	if (dp[i][z][o] != -1)
	{
		return dp[i][z][o];
	}
	int ans = 0;
	int p1 = _f2(strs, strsSize, i + 1, z, o, dp);
	_count(strs[i]);
	int p2 = 0;
	if (z >= _zeros && o >= _ones)
	{
		p2 = _f2(strs, strsSize, i + 1, z - _zeros, o - _ones, dp) + 1;
	}
	ans = _max(p1, p2);
	dp[i][z][o] = ans;
	return ans;
}

int f2(char** strs, int strsSize, int m, int n)
{
	// 最外层的申请。
	int*** dp = (int***)malloc(strsSize * sizeof(int**));
	for (int i = 0; i < strsSize; ++i)
	{
		// 申请中间层。
		dp[i] = (int**)malloc((m + 1) * sizeof(int*));
		for (int j = 0; j <= m; ++j)
		{
			// 申请最内层。
			dp[i][j] = (int*)malloc((n + 1) * sizeof(int));
			for (int k = 0; k <= n; ++k)
			{
				dp[i][j][k] = -1;
			}
		}
	}
	int ans = _f2(strs, strsSize, 0, m, n, dp);
	for (int i = 0; i < strsSize; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			free(dp[i][j]);
			dp[i][j] = NULL;
		}
		free(dp[i]);
		dp[i] = NULL;
	}
	free(dp);
	dp = NULL;
	return ans;
}


// $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
// 严格位置依赖的动态规划。

int f3(char** strs, int strsSize, int m, int n)
{
	// 如果是GCC编译器C99支持变长数组。
	//dp[strsSize + 1][m + 1][n + 1];
	// 最外层的申请。
	int*** dp = (int***)malloc((strsSize + 1) * sizeof(int**));
	for (int i = 0; i <= strsSize; ++i)
	{
		// 申请中间层。
		dp[i] = (int**)malloc((m + 1) * sizeof(int*));
		for (int j = 0; j <= m; ++j)
		{
			// 申请最内层。
			dp[i][j] = (int*)malloc((n + 1) * sizeof(int));
			for (int k = 0; (k <= n) && (i == strsSize); ++k)
			{
				dp[i][j][k] = 0;
			}
		}
	}
	// 最上面一层都是0.

	// 计算。
	for (int i = strsSize - 1; i >= 0; --i)
	{
		_count(strs[i]);
		for (int z = 0, p1 = 0, p2 = 0; z <= m; ++z)
		{
			for (int o = 0; o <= n; ++o)
			{
				p1 = dp[i + 1][z][o];
				p2 = 0;
				if (z >= _zeros && o >= _ones)
				{
					p2 = 1 + dp[i + 1][z - _zeros][o - _ones];
				}
				dp[i][z][o] = _max(p1, p2);
			}
		}
	}
	int ans = dp[0][m][n];
	// 释放内存。
	for (int i = 0; i < strsSize; ++i)
	{
		for (int j = 0; j <= m; ++j)
		{
			free(dp[i][j]);
			dp[i][j] = NULL;
		}
		free(dp[i]);
		dp[i] = NULL;
	}
	free(dp);
	dp = NULL;
	return ans;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
// 空间压缩的动态规划。

int f4(char** strs, int strsSize, int m, int n)
{

	int** dp = (int**)malloc((m + 1) * sizeof(int*));
	for (int z = 0; z <= m; ++z)
	{
		dp[z] = (int*)malloc((n + 1) * sizeof(int));
		for (int o = 0; o <= n; ++o)
		{
			dp[z][o] = 0;
		}
	}
	for (int i = 0; i < strsSize; ++i)
	{
		_count(strs[i]);
		for (int z = m; z >= _zeros; --z)
		{
			for (int o = n; o >= _ones; --o)
			{
				dp[z][o] = _max(dp[z][o], 1 + dp[z - _zeros][o - _ones]);
			}
		}
	}
	int ans = dp[m][n];
	for (int i = 0; i <= m; ++i)
	{
		free(dp[i]);
		dp[i] = NULL;
	}
	free(dp);
	dp = NULL;	
	return ans;
}

// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@


int findMaxForm(char** strs, int strsSize, int m, int n)
{
	//return f1(strs, strsSize, m, n); --> 通过不了。
	//return f2(strs, strsSize, m, n); // --> 挂一个傻傻的缓存表。
	//return f3(strs, strsSize, m, n); // --> 严格位置依赖的动态规划。
	return f4(strs, strsSize, m, n); // --> 空间压缩的动态规划。
}