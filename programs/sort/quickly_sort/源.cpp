#include<stdio.h>
//time complexity O(nlog2^n)
//space complexity O(nlog2^n)
//unstable
void exchange(int a[], int i, int j)
{
	a[i] = a[i] ^ a[j];
	a[j] = a[i] ^ a[j];
	a[i] = a[i] ^ a[j];
	return;

}

void quick_sort(int a[], int left, int right)
{
	int p = left, min = left + 1, max = right;
	if (left >= right)          //递归终止条件
	{
		return;
	}
	while (min < max)
	{
		while (min < max && a[max] >= a[p])  //右侧开始比较
			max--;
		while (min < max && a[min] < a[p]) //左侧开始比较
			min++;
		if (min < max)                      //交换
		{
			exchange(a, max, min);
		}
	}										//找到位置，交换
	if (a[p] > a[min])						//min 没有被判断，max一直--
		exchange(a, p, min);
	else
	{
		min = p; max = p;
	}

	quick_sort(a, left, min - 1);//递归左侧
	quick_sort(a, max + 1, right);//递归右侧
}
int main(void)
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	int b[sizeof a / sizeof a[0]];
	quick_sort(a, 0, sizeof a / sizeof a[0] - 1);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}