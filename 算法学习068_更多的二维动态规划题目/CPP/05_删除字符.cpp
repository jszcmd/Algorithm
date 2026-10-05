// 2026年10月06日。

// 删除至少几个字符可以变成另一个字符串的子串
// 给定两个字符串s1和s2
// 返回s1至少删除多少字符可以成为s2的子串
// 对数器验证

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>   // 用了 time(0)
using std::endl;
using std::cout;
using std::vector;
using std::string;
using std::min;
using std::sort;

// 生成s1字符串的所有子序列串
void _f1(const string& s1, int i, string& path, vector<string>& list)
{
	if (i == s1.length())
	{
		list.push_back(path);
	}
	else
	{
		_f1(s1, i + 1, path, list);       // 不选
		path.push_back(s1[i]);            // 选
		_f1(s1, i + 1, path, list);       
		path.pop_back();                  // 回溯
	}
}

struct str_len_cmp
{
	bool operator()(const string& a, const string& b)
	{
		return a.size() > b.size();   // 长度大的排在前面（降序）
	}
};

int f1(const string& s1, const string& s2)
{
	vector<string> v1;
	string s_;
	_f1(s1, 0, s_, v1);
	sort(v1.begin(), v1.end(), str_len_cmp());
	for (auto& str : v1)
	{
		if (s2.find(str) != string::npos)
		{
			return s1.length() - str.length();
		}
	}
	return (int)s1.length(); // s1需要把自己全部删除掉。
}

// dp[i][j] : s1[前缀长度为i]至少删除多少字符，可以变成s2[前缀长度为j]的任意后缀串
// (1): s1[i-1] != s2[j-1]。
//     把s1[i-1]位置删除掉。 dp[i][j] = 1 + dp[i-1][j]
// (2): s1[i-1] == s2[j-1]
//     dp[i][j] = dp[i-1][j-1]

int f2(const string& s1, const string& s2)
{
	int n = s1.length();
	int m = s2.length();
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; ++i)
	{
		dp[i][0] = i;
		for (int j = 1; j <= m; ++j)
		{
			if (s1[i - 1] == s2[j - 1])
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = dp[i - 1][j] + 1;
			}
		}
	}
	int ans = dp[n][0];
	for (int j = 1; j <= m; ++j)
	{
		ans = min(ans, dp[n][j]);
	}
	return ans;
}

// 生成长度为 n，有 v 种字符（'a' ~ 'a'+v-1）的随机字符串
string randomString(int n, int v)
{
	std::string ans(n, 'a');
	for (int i = 0; i < n; i++)
	{
		ans[i] = (char)('a' + (rand() % v));
	}
	return ans;
}

int main()
{
	srand((unsigned int)time(0));
	int n = 12;
	int v = 6;
	int testTime = 20000;
	cout << "测试开始:" << endl;
	for (int i = 0; i < testTime; ++i)
	{
		int len1 = (rand() % n) + 1; // [1,n]
		int len2 = (rand() % n) + 1;
		string s1 = randomString(len1, v);
		string s2 = randomString(len2, v);
		int ans1 = f1(s1, s2);
		int ans2 = f2(s1, s2);
		if (ans1 != ans2)
		{
			cout << "出错了!!!" << endl;
		}
	}
	cout << "测试结束。" << endl;
	return 0;
}