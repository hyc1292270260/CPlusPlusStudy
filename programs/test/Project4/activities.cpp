//#include<stdio.h>
//#include <algorithm>
//using namespace std;
//#define max_v 100
////活动
//struct node
//{
//	int i;
//	int end_time;
//	int start_time;
//	int flag;
//};
//bool cmp(node a, node b)
//{
//	return a.end_time < b.end_time;
//}
//int main()
//{
//	struct node p[max_v];
//	int n;
//	scanf("%d", &n);
//	for (int i = 0; i < n; i++)
//	{
//		scanf("%d %d %d", &p[i].i, &p[i].start_time, &p[i].end_time);
//		p[i].i = i + 1;
//		p[i].flag = 0;
//	}
//	sort(p, p + n, cmp);
//	int sum = 1;
//	int end_time;
//	end_time = p[0].end_time;
//	p[0].flag = 1;
//	for (int i = 1; i < n; i++)
//	{
//		if (p[i].start_time >= end_time)
//		{
//			sum++;
//			p[i].flag = 1;
//			end_time = p[i].end_time;
//		}
//	}
//	printf("sum=%d\n", sum);
//	printf("活动编号：\n");
//	for (int i = 0; i < n; i++)
//	{
//		printf("%d ", p[i].i);
//	}
//	printf("\n");
//	return 0;
//}
