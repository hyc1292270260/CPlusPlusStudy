#include <stdio.h>
void bubble_sort(int a[], int n) 
{

	int i, j, temp; int finish = 0;
	for (i = 0; (i < n)&&(finish = 0); i++)
	{
		for (j = 0, finish = 1; j < n - i; j++) 
	   {
			if (a[j] > a[j + 1])
			{
				finish = 0;
				temp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = temp;
			}
		}
	}
}
		int main(void) {
			int a[10]{1,9,9,8,7,6,5,1,3,5}, i;
			bubble_sort( a, 10);
			for (i = 0; i < 10; i++)
				printf("%d", a[i]);
			return 0;
		}


	
	
	