#include <stdio.h>
//time complexity O(nlog2^n)
//space complexity O(n)
//stable
//归并排序,分治法
void merge(int a[], int min_l, int max_l, int min_r, int max_r, int temp[])
{
	int i, j, k;
	i = min_l;
	j = min_r;
	for (k = min_l; k <= max_r; ++k)
	{
		if (i <= max_l && j <= max_r)
		{
			if (a[i] <= a[j])
				temp[k] = a[i++];
			else
				temp[k] = a[j++];
		}
		else if (i > max_l)
			temp[k] = a[j++];
		else
			temp[k] = a[i++];
	}
	//数据回填
	for (k = min_l; k <= max_r; ++k)
		a[k] = temp[k];

}

void merging_sort(int a[], int min, int max, int temp[])
{
	int mid = (min + max) / 2;//分割点
	if (min >= max)                  //递归终止条件
		return;
	//递归
	merging_sort(a, min, mid, temp); 
	merging_sort(a, mid + 1, max, temp);
	merge(a, min, mid, mid + 1, max, temp);
	return;

}
int main(void)
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	int b[sizeof a / sizeof a[0]];
	merging_sort(a, 0, (sizeof a / sizeof a[0]) - 1, b);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}