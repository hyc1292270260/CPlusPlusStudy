//#include <iostream> 
////背包
//int Package(int n, int w[], int p[], int v)
// {
//	//设置一个二维数组，横坐标代表从第一个物品开始放到第几个物品，纵坐标代表背包还有多少容量，dp代表最大价值
//	int dp[n+1][v+1] = new int[n + 1][v + 1];
//	for (int i = 1; i < n + 1; i++)
//	{
//		for (int j = 1; j <= v; j++)
//		{
//			if (j >= w[i])
//			{
//				/*
//				 * 当能放得下这个物品时，放下这个物品，价值增加，但是空间减小，最大价值是dp[i-1][j-w[i]]+p[i]
//				 * 当不放这个物品时，空间大，物品还是到i-1，最大价值是dp[i-1][j]
//				 * 比较这两个大小，取最大的，就是dp[i][j]
//				 */
//				dp[i][j] = __max(dp[i - 1][j], dp[i - 1][j - w[i]] + p[i]);
//			}
//			else {
//				//如果放不下，就是放上一个物品时的dp
//				dp[i][j] = dp[i - 1][j];
//			}
//		}
//	}
//	return dp[n][v];
//}
//
// int main(void)
// {
//
//	 cin >>
//	 return 0;
//
// }