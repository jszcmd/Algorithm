// 有效涂色问题
// 给定n、m两个参数
// 一共有n个格子，每个格子可以涂上一种颜色，颜色在m种里选
// 当涂满n个格子，并且m种颜色都使用了，叫一种有效方法
// 求一共有多少种有效的涂色方法
// 1 <= n, m <= 5000
// 结果比较大请 % 1000000007 之后返回
// 对数器验证

// dp[i][j] 前i个格子,涂了j种颜色的方法数。

// (1): dp[i-1][j] * j 从前面的i-1个格子,使用了j种颜色,从其中选出来一种,涂上i格子。
// (2): dp[i-1][j-1] * (m-(j-1)) 前面i-1个格子筹齐了j-1种,第i个格子再选出来一种新的颜色。

#include <cstdlib>   // rand, srand
#include <ctime>     // time
#include <iostream>
#include <vector>
#include <algorithm> // fill
#define MOD 1000000007
#define MAXN 5001
using std::vector;
using std::cout;
using std::endl;
using std::fill;

int _f1(vector<int>& path, vector<bool>& set, int i, int n, int m)
{
	if (i == n) // 填写到头了。
	{
		fill(set.begin(), set.end(), false);
		int colors = 0; // 开始统计。
		for (auto c : path)
		{
			if (!set[c]) // 第一次统计
			{
				set[c] = true;
				colors++;
			}
		}
		return colors == m ? 1 : 0; // 用满 m 种 → 有效，否则无效
	}
	else
	{
		int ans = 0;
		for (int j = 1; j <= m; ++j) // 第i个格子m种颜色都试一试。
		{
			path[i] = j; // 填写上第j种颜色。
			ans = (ans + _f1(path, set, i + 1, n, m)) % MOD;  // 递归填下一个格子
		}
		return ans;
	}
}

// v1 表示路径。 v1[0]表示第一个格子填写第几个(可以是1到m中的任何一个)编号的颜色...v1[n-1] 表示最后一个格子
// b1 用于统计 b1[x] 表示第x编号的颜色的是不是存在,是否被使用。
int f1(int n, int m)
{
	vector<int> v1(n, 0);
	vector<bool> b1(m + 1);
	return _f1(v1, b1, 0, n, m);
}


int f2(int n, int m)
{
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; ++i)
	{
		dp[i][1] = m;
	}
	for (int i = 2; i <= n; ++i)
	{
		for (int j = 2; j <= m; ++j)
		{
			dp[i][j] = (int)(((long long)dp[i - 1][j] * j) % MOD);
			dp[i][j] = (int)((((long long)dp[i - 1][j - 1] * (m - j + 1)) + dp[i][j]) % MOD);
		}
	}
	return dp[n][m];
}


int main()
{
	srand((unsigned int)time(0));

	int N = 7;
	int M = 7;
	cout << "功能测试开始:" << endl;
	for (int n = 1; n <= N; ++n)
	{
		for (int m = 1; m <= M; ++m)
		{
			int ans1 = f1(n, m);
			int ans2 = f2(n, m);
			if (ans1 != ans2)
			{
				cout << "出错了!!!" << endl;
			}
		}
	}
	cout << "功能测试结束。" << endl;

	cout << "性能测试开始: " << endl;
	int n = 5000;
	int m = 4877;
	cout << "n : " << n << endl;
	cout << "m : " << m << endl;
	clock_t start = clock();
	int ans2 = f2(n, m);
	clock_t end = clock();
	double ms = (double)(end - start) / CLOCKS_PER_SEC * 1000;
	cout << "取模之后的结果: " << ans2 << endl;
	cout << "运行时间: " << ms << "毫秒" << endl;
	cout << "性能测试结束" << endl;
	
	return 0;
}