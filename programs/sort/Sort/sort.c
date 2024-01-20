#include <stdio.h>


//void quick_sort(int a[], int left, int right);
//void bubble_sort(int a[], int n);
//void merging_sort(int a[], int min, int max, int temp[]);
//void straihgt_insert(int a[], int n);
//void shell_sort(int a[], int n);
void select_sort(int a[], int n);
//time complexity O(n^2)
//space complexity O(1)
//unstable
int main(void)
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	//int b[sizeof a / sizeof a[0]];
	select_sort(a, sizeof a / sizeof a[0]);
	//quick_sort(a, 0, sizeof a / sizeof a[0] - 1);
	//bubble_sort(a, sizeof a / sizeof a[0]);
	//straihgt_insert(a, sizeof a / sizeof a[0]);
	//shell_sort(a, sizeof a / sizeof a[0]);
	//merging_sort(a, 0, (sizeof a / sizeof a[0]) - 1, b);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}
void exchange(int a[], int i, int j)
{
	int  temp;
	temp = a[i];
	a[i] = a[j];
	a[j] = temp;
	return;

}
void select_sort(int a[], int n)
{
	int i, j, min_dex;
	for (i = 0; i < n - 1; ++i)
	{
		 min_dex = i;
		for (j = i + 1; j < n; ++j)
			if (a[j] < a[min_dex])
				min_dex =j;
		if (min_dex != i)
		{
			exchange(a, min_dex, i);
		}
	}
	

}

