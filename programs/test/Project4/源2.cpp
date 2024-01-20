//#include <iostream>
//#include <vector>
//using namespace std;
//vector<int>vec;
////最长子序列
//int MaxContinueArraySum(vector<int>vec)
//{
//	int n = vec.size();
//	int max = vec[0];
//	int sum = vec[0];
//	for (int i = 1; i < n; i++)
//	{
//
//		if (sum + vec[i] >= vec[i])
//		{
//			sum = sum + vec[i];
//		}
//		else
//			sum = vec[i];
//		if (sum > max)
//		{
//			max = sum;
//		}
//	}
//	return max;
//}
//int main(void)
//{
//	int m ,num;
//	std::cin >> m;
//	
//	for (int i = 0;i<m;++i)
//	{
//		cin >> num;
//		vec.emplace_back(num);
//	}
//	
//	cout << MaxContinueArraySum(vec);
//	return 0;
//	
//}