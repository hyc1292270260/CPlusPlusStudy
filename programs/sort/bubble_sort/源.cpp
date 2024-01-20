#include<stdio.h>
//time complexity O(n^2)
//space complexity O(1)
//stable
void bubble_sort(int a[], int n)
{

	int i, j; int finish = 0;
	for (i = 0; i < n-1  && !finish ; ++i)
	{
		for (j = 0, finish = 1; j < n - i - 1; ++j)
		{
			if (a[j] > a[j + 1])						//设置标志位，若没有交换则已完成排序
			{
				finish = 0;
				int  temp;
				temp = a[j];
				a[j] = a[j+1];
				a[j+1] = temp;
				
			}
		}
	}

}

int main(void)
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	
	bubble_sort(a, sizeof a / sizeof a[0]);
	for (i = 0; i < (sizeof a / sizeof a[0]); ++i)
		printf("%3i", a[i]);
	return 0;
}