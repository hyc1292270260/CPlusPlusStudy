#include<stdio.h>
//time complexity O(n^2)
//space complexity O(1)
//stable
void straight_insert(int a[], int n)
{
	int i, j, temp;
	for (i = 1; i < n; ++i)
	{
		temp = a[i];
		for (j = i - 1; j >= 0 && a[j] > temp; j--)
			a[j + 1] = a[j];
		a[j + 1] = temp;
	}
}
int main(void)                               //Œ»∂®
{
	int i;
	int a[] = { 4,2,1,6,9,8,6,7,4,3 };
	int b[sizeof a / sizeof a[0]];
	straight_insert(a, sizeof a[0]);
	for (i = 0; i < (sizeof a / sizeof a[0]); i++)
		printf("%3i", a[i]);
	return 0;
}