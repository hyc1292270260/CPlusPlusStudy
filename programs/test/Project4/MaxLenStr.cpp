//#include<iostream>
//#include<vector>
//using namespace std;
////最长子序列
//int MaxLenStr(vector<int> vec)
//{
//	int len = vec.size();
//	vector<int> dp(len, 1);
//	int maxLen = 1;
//	for (int i = 0; i < len; i++)
//	{
//		for (int j = i - 1; j >= 0; j--)
//		{
//			if (vec[i] > vec[j] && dp[i] < dp[j] + 1)
//			{
//				dp[i] = dp[j] + 1;
//			}
//		}
//		if (maxLen < dp[i])
//			maxLen = dp[i];
//	}
//	return maxLen;
//}
//
//int main()
//{
//	int n;
//	vector<int> vec;
//	cin >> n;
//	for (int i = 0; i < n; i++)
//	{
//		int number;
//		cin >> number;
//		vec.push_back(number);
//	}
//	int maxLen = MaxLenStr(vec);
//	cout << maxLen << endl;
//	return 0;
//}
