//#include <iostream>
//
//using namespace std;
//int current_water(int m, int t, int m1, int t1, int m2, int t2);
//int main(void)
//{
//	unsigned n;
//	cin >> n;
//	int* a = new int[n * 6];
//	for (int i = 0; i < n * 6; i += 6)
//	{
//		cin >> a[i] >> a[i + 1] >> a[i + 2] >> a[i + 3] >> a[i + 4] >> a[i + 5];
//
//	}
//	for (int i = 0; i < n * 6; i += 6)
//	{
//		cout << current_water(a[i], a[i + 1], a[i + 2], a[i + 3], a[i + 4], a[i + 5]) << endl;
//	}
//	return 0;
//}
//int current_water(int m, int t, int m1, int t1, int m2, int t2)
//{
//	short in = 1, out = 1;
//	int cur_w = 0, cur_m = 0;
//	for (int i = 1; i <= t; ++i)
//	{
//		cur_m = m1 * in - m2 * out;
//		cur_w += cur_m;
//		if (cur_w < 0)
//		{
//			cur_w = 0;
//		}
//		if (cur_w > m)
//		{
//			cur_w = m;
//		}
//		if (i%t1 == 0)
//		{
//			in = (in == 1 ? 0 : 1);
//		}
//		if (i%t2 == 0)
//		{
//			out = (out == 1 ? 0 : 1);
//		}
//		
//		
//	}
//	return cur_w;
//}