#include <stdio.h>
#include<vector>
using namespace std;

vector<long long int>a;
vector<int>num;
int main(void)
{
	int n, max = 0;
	long long int b;
	scanf("%d", &n);

	for (int i = 0; i < n; ++i)
	{
		scanf("%d", &b);
		a.emplace_back(b);



	}
	for (int i = 0; i < n; ++i)
	{
		num[i] = 1;
		for (int j = 0; j < i; ++j)
		{
			if (a[j]<a[i] && num[j] + 1>num[j])
			{
				num[i] = num[j] + 1;
			}
		}
	}
	for (int i = 0; i < n; ++i)
	{
		if (max < num[i])
		{
			max = num[i];
		}
	}
	printf("%d", max);
	return 0;
}