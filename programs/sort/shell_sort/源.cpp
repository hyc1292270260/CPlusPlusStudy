#include<stdio.h>
//time complexity O(n^1.3)
//space complexity O(1)
//unstable
void shell_sort(int a[], int n)
{
	int i, j, k, temp;
	for (k = n / 2; k >= 1; k /= 2)					//分组
	{
		for (i = k; i < n; ++i)						//所以组一起排序
		{
			temp = a[i];
			for (j = i - k; j >= 0 && a[j] > temp; j -= k)
				a[j + k] = a[j];
			a[j + k] = temp;
		}
	}

}
int main(void)                                     //不稳定
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	int b[sizeof a / sizeof a[0]];
	shell_sort(a, sizeof a / sizeof a[0]);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}